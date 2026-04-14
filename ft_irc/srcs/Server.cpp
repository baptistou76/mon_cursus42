/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:20:23 by bcaumont          #+#    #+#             */
/*   Updated: 2026/01/13 14:31:04 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"
#include "signal.hpp"
#include <sys/socket.h>

Server::Server(int port, const std::string &password) : _port(port),
	_password(password)
{
	int			opt;
	sockaddr_in	addr;

	_name = "ircserv";
	_serverFd = socket(AF_INET, SOCK_STREAM, 0);
	if (_serverFd < 0)
		throw std::runtime_error("Socket failed");
	opt = 1;
	if (setsockopt(_serverFd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) < 0)
		throw std::runtime_error("setsockopt failed");
	std::memset(&addr, 0, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(_port);
	if (bind(_serverFd, (sockaddr *)&addr, sizeof(addr)) < 0)
		throw std::runtime_error("Bind failed");
	if (listen(_serverFd, 10) < 0)
		throw std::runtime_error("Listen failed");
}

Server::~Server()
{
	for (std::map<int,
		Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
		delete (it->second);
	for (std::map<std::string,
		Channel *>::iterator it = _channels.begin(); it != _channels.end(); ++it)
		delete (it->second);
	if (_serverFd != -1)
		close(_serverFd);
}

bool Server::isMarkedForRemoval(int fd) const
{
	return (_toRemove.find(fd) != _toRemove.end());
}

void Server::markClientForRemoval(int fd)
{
	if (_toRemove.find(fd) != _toRemove.end())
		return ;
	_toRemove.insert(fd);
	shutdown(fd, SHUT_RDWR);
}

void Server::cleanupRemovals(std::vector<pollfd> &pollfds)
{
	int	fd;

	for (std::set<int>::iterator it = _toRemove.begin(); it != _toRemove.end(); ++it)
	{
		fd = *it;
		std::cout << "Client disconnected: FD= " << fd << std::endl;
		removeClient(fd);
		for (size_t i = 0; i < pollfds.size(); ++i)
		{
			if (pollfds[i].fd == fd)
			{
				pollfds.erase(pollfds.begin() + i);
				break ;
			}
		}
	}
	_toRemove.clear();
}

void Server::run()
{
	struct sockaddr_in	addr;
	socklen_t			addrLen;
	pollfd				serverPoll;
	int					ret;
	pollfd				clientPoll;
	int					clientFd;
	Client				*client;
	char				buffer[512];
	int					bytesRead;

	addrLen = sizeof(addr);
	fcntl(_serverFd, F_SETFL, O_NONBLOCK);
	std::vector<pollfd> pollfds;
	serverPoll.fd = _serverFd;
	serverPoll.events = POLLIN;
	serverPoll.revents = 0;
	pollfds.push_back(serverPoll);
	std::cout << "Server running on port " << _port << std::endl;
	while (g_running)
	{
		if (!_toRemove.empty())
			cleanupRemovals(pollfds);
		for (size_t i = 0; i < pollfds.size(); ++i)
		{
			pollfds[i].events = POLLIN;
			if (pollfds[i].fd != _serverFd)
			{
				client = _clients[pollfds[i].fd];
				if (client && client->hasPending())
					pollfds[i].events |= POLLOUT;
			}
		}
		ret = poll(pollfds.data(), pollfds.size(), -1);
		if (ret < 0)
			throw std::runtime_error("Poll failed");
		for (size_t i = 0; i < pollfds.size(); ++i)
		{
			if (pollfds[i].fd != _serverFd
				&& (pollfds[i].revents & (POLLHUP | POLLERR | POLLNVAL)))
			{
				std::cout << "Client disconnected: FD= " << pollfds[i].fd << std::endl;
				markClientForRemoval(pollfds[i].fd);
				continue ;
			}
			if (pollfds[i].fd != _serverFd && (pollfds[i].revents & POLLOUT))
			{
				clientFd = pollfds[i].fd;
				client = _clients[clientFd];
				if (client && !client->flushSend())
				{
					std::cout << "Client send error: FD= " << clientFd << std::endl;
					markClientForRemoval(clientFd);
					continue ;
				}
			}
			if (!(pollfds[i].revents & POLLIN))
				continue ;
			if (pollfds[i].fd == _serverFd)
			{
				if (pollfds[i].revents & (POLLERR | POLLHUP | POLLNVAL))
					continue ;
				clientFd = accept(_serverFd, (struct sockaddr *)&addr,
						&addrLen);
				if (clientFd < 0)
					continue ;
				fcntl(clientFd, F_SETFL, O_NONBLOCK);
				addClient(clientFd);
				clientPoll.fd = clientFd;
				clientPoll.events = POLLIN;
				clientPoll.revents = 0;
				pollfds.push_back(clientPoll);
				std::cout << "New client connected: FD= " << clientFd << std::endl;
			}
			else
			{
				clientFd = pollfds[i].fd;
				if (isMarkedForRemoval(clientFd))
					continue ;
				client = _clients[clientFd];
				if (!client)
					continue ;
				bytesRead = recv(clientFd, buffer, sizeof(buffer) - 1, 0);
				if (bytesRead <= 0)
				{
					markClientForRemoval(clientFd);
					continue ;
				}
				buffer[bytesRead] = '\0';
				client->addToBuffer(std::string(buffer));
				std::string cmd;
				while (!(cmd = client->extractCommand()).empty())
				{
					handleClientMessage(clientFd, cmd);
					if (isMarkedForRemoval(clientFd))
						break ;
				}
			}
		}
		if (!_toRemove.empty())
			cleanupRemovals(pollfds);
	}
}

int Server::getServerFd() const
{
	return (_serverFd);
}

void Server::addClient(int fd)
{
	Client	*client;

	client = new Client(fd);
	_clients[fd] = client;
}

void Server::removeClient(int fd)
{
	std::map<int, Client *>::iterator it = _clients.find(fd);
	if (it != _clients.end())
	{
		delete (it->second);
		_clients.erase(it);
	}
}

Client *Server::getClientByNick(const std::string &nickname)
{
	for (std::map<int,
		Client *>::iterator it = _clients.begin(); it != _clients.end(); ++it)
	{
		if (it->second->getNickname() == nickname)
			return (it->second);
	}
	return (NULL);
}

std::string Server::getName() const
{
	return (_name);
}

Channel *Server::getChannel(const std::string &name)
{
	std::map<std::string, Channel *>::iterator it = _channels.find(name);
	if (it != _channels.end())
		return (it->second);
	return (NULL);
}

Channel *Server::createChannel(const std::string &name)
{
	Channel	*newChannel;

	newChannel = new Channel(name);
	_channels[name] = newChannel;
	return (newChannel);
}

const std::map<std::string, Channel *> &Server::getChannels() const
{
	return (_channels);
}

void Server::removeChannel(const std::string &name)
{
	std::map<std::string, Channel *>::iterator it = _channels.find(name);
	if (it != _channels.end())
	{
		delete (it->second);
		_channels.erase(it);
	}
}

void Server::handleClientMessage(int clientFd, const std::string &message)
{
	Client	*client;

	client = _clients[clientFd];
	if (!client)
		return ;
	_cmdHandler.handle(*this, *client, message);
}

const std::string &Server::getPassword() const
{
	return (_password);
}

void Server::tryRegister(Client &client)
{
	if (client.isRegistered())
		return ;
	if (!client.isPassOk())
		return ;
	if (!client.hasNickname())
		return ;
	if (client.getUsername().empty())
		return ;
	client.setRegistered(true);
	sendReply(*this, client, RPL_WELCOME, "", "Welcome to IRC "
		+ client.toString());
	sendReply(*this, client, RPL_YOURHOST, "", "Your host is " + getName());
	sendReply(*this, client, RPL_CREATED, "",
		"This server was created just now");
	sendReply(*this, client, RPL_MYINFO, getName() + " ft_irc i t k o l", "");
}
