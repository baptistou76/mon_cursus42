/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CommandHandler.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/05 17:48:23 by bcaumont          #+#    #+#             */
/*   Updated: 2026/01/02 16:30:06 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "CapCmd.hpp"
#include "Client.hpp"
#include "CommandHandler.hpp"
#include "InviteCmd.hpp"
#include "JoinCmd.hpp"
#include "KickCmd.hpp"
#include "ModeCmd.hpp"
#include "NickCmd.hpp"
#include "PartCmd.hpp"
#include "PassCmd.hpp"
#include "PingCmd.hpp"
#include "PrivMsgCmd.hpp"
#include "QuitCmd.hpp"
#include "Server.hpp"
#include "TopicCmd.hpp"
#include "UserCmd.hpp"
#include <cctype>
#include <algorithm>
#include "Utils.hpp"

CommandHandler::CommandHandler()
{
	registerCommand("PASS", new PassCmd());
	registerCommand("NICK", new NickCmd());
	registerCommand("USER", new UserCmd());
	registerCommand("PING", new PingCmd());
	registerCommand("JOIN", new JoinCmd());
	registerCommand("PRIVMSG", new PrivMsgCmd());
	registerCommand("KICK", new KickCmd());
	registerCommand("INVITE", new InviteCmd());
	registerCommand("MODE", new ModeCmd());
	registerCommand("TOPIC", new TopicCmd());
	registerCommand("PART", new PartCmd());
	registerCommand("QUIT", new QuitCmd());
	registerCommand("CAP", new CapCmd());
}

CommandHandler::CommandHandler(const CommandHandler &copy)
{
	(void)copy;
}

CommandHandler &CommandHandler::operator=(const CommandHandler &copy)
{
	(void)copy;
	return (*this);
}

CommandHandler::~CommandHandler()
{
	for (std::map<std::string,
		ICommand *>::iterator it = _commands.begin(); it != _commands.end(); ++it)
		delete (it->second);
}

void CommandHandler::registerCommand(const std::string &name, ICommand *cmd)
{
	if (!cmd)
		return ;
	_commands[name] = cmd;
}

void CommandHandler::handle(Server &server, Client &client,
	const std::string &cmd)
{
	if (cmd.empty())
		return ;

	std::istringstream ss(cmd);
	std::string cmdName;
	ss >> cmdName;
	std::transform(cmdName.begin(), cmdName.end(), cmdName.begin(),
	::toupper);
	std::vector<std::string> args;
	std::string token;

	while (ss >> token)
	{
		if (!token.empty() && token[0] == ':')
		{
			std::string trailing = token.substr(1);
			std::string rest;
			std::getline(ss, rest);
			if (!rest.empty())
				trailing += rest;
			args.push_back(trailing);
			break ;
		}
		args.push_back(token);
	}

	std::map<std::string, ICommand *>::iterator it = _commands.find(cmdName);
	if (it != _commands.end())
		it->second->execute(server, client, args);
	else
		sendError(server, client, ERR_UNKNOWNCOMMAND, cmdName, "Unknown command");
}
