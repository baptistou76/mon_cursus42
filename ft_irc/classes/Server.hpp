/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Server.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/04 19:19:01 by bcaumont          #+#    #+#             */
/*   Updated: 2026/01/02 16:49:19 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SERVER_HPP
# define SERVER_HPP

# include "Channel.hpp"
# include "Client.hpp"
# include "CommandHandler.hpp"
# include "ft_irc.hpp"
# include <set>

class	Channel;
class	Client;

class Server
{
  private:
	Server(const Server &);
	Server &operator=(const Server &);
	int _port;
	std::string _password;
	int _serverFd;
	std::string _name;
	std::map<int, Client *> _clients;
	std::map<std::string, Channel *> _channels;
	CommandHandler _cmdHandler;

	std::set<int> _toRemove;

	bool isMarkedForRemoval(int fd) const;
	void cleanupRemovals(std::vector<pollfd> &pollfds);

  public:
	Server(int port, const std::string &password);
	~Server();

	void run();

	void addClient(int fd);
	void removeClient(int fd);
	void markClientForRemoval(int fd);
	std::string getName() const;
	Client *getClientByNick(const std::string &nickname);

	Channel *getChannel(const std::string &name);
	Channel *createChannel(const std::string &name);
	void removeChannel(const std::string &name);
	const std::map<std::string, Channel *> &getChannels() const;

	void handleClientMessage(int clientFd, const std::string &message);
	void tryRegister(Client &client);
	int getServerFd() const;
	const std::string &getPassword() const;
};

#endif
