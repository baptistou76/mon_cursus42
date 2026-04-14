/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Client.cpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 20:30:18 by bcaumont          #+#    #+#             */
/*   Updated: 2025/12/13 08:29:19 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "ft_irc.hpp"
#include <cerrno>
#include <sys/socket.h>

Client::Client(int fd) : _fd(fd), _registered(false), _passOk(false)
{
}

Client::Client(const Client &copy)
{
	*this = copy;
}

Client &Client::operator=(const Client &copy)
{
	if (this != &copy)
	{
		_nickname = copy._nickname;
		_username = copy._username;
		_buffer = copy._buffer;
		_out = copy._out;
		_fd = copy._fd;
		_registered = copy._registered;
		_passOk = copy._passOk;
	}
	return (*this);
}

Client::~Client()
{
	close(_fd);
}

int Client::getFd() const
{
	return (_fd);
}

const std::string &Client::getNickname() const
{
	return (_nickname);
}

const std::string &Client::getUsername() const
{
	return (_username);
}

bool Client::isRegistered() const
{
	return (_registered);
}

void Client::setNickname(const std::string &nick)
{
	_nickname = nick;
}

void Client::setUsername(const std::string &user)
{
	_username = user;
}

void Client::setRegistered(bool state)
{
	_registered = state;
}

void Client::addToBuffer(const std::string &data)
{
	_buffer += data;
}

bool Client::hasNickname() const
{
	return (!_nickname.empty());
}

void Client::Registered()
{
	_registered = true;
}

bool Client::isPassOk() const
{
	return (_passOk);
}

void Client::setPassOk(bool v)
{
	_passOk = v;
}

std::string Client::toString() const
{
	return (_nickname + " (" + _username + ")");
}

std::string Client::extractCommand()
{
	size_t pos = _buffer.find('\n');
	std::string cmd;

	if (pos == std::string::npos)
		return ("");

	cmd = _buffer.substr(0, pos);

	if (!cmd.empty() && cmd[cmd.size() - 1] == '\r')
		cmd.erase(cmd.size() - 1);

	_buffer.erase(0, pos + 1);
	return (cmd);
}

bool Client::hasPending() const
{
	return (!_out.empty());
}

void Client::sendMessage(const std::string &msg)
{
	_out += msg;
	if (_out.size() < 2 || _out.compare(_out.size() - 2, 2, "\r\n") != 0)
		_out += "\r\n";
}

bool Client::flushSend()
{
	while (!_out.empty())
	{
		ssize_t n = send(_fd, _out.c_str(), _out.size(), MSG_NOSIGNAL);
		if (n > 0)
			_out.erase(0, n);
		else if (n == -1 && (errno == EAGAIN || errno == EWOULDBLOCK))
			return (true);
		else
			return (false);
	}
	return (true);
}
