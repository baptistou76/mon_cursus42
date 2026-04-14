/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   NickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:22:54 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 21:02:08 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "NickCmd.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Utils.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

static bool isNickFirstChar(char c)
{
	if ((c >= 'A' && c <= 'Z') || (c >= 'a' && c <= 'z'))
		return (true);
	return (c == '[' || c == ']' || c == '\\' || c == '`'
		|| c == '_' || c == '^' || c == '{' || c == '}' || c == '|');
}

static bool isNickChar(char c)
{
	if (isNickFirstChar(c))
		return (true);
	if (c >= '0' && c <= '9')
		return (true);
	return (c == '-');
}

static bool isValidNick(const std::string &nick)
{
	if (nick.empty() || nick.size() > 30)
		return (false);
	if (!isNickFirstChar(nick[0]))
		return (false);
	for (size_t i = 0; i < nick.size(); ++i)
	{
		unsigned char c = nick[i];
		if (c < 0x20 || c == 0x7F)
			return (false);
		if (c == ' ' || c == ',' || c == '*' || c == '?' || c == '!'
			|| c == '@' || c == '#' || c == ':' || c == '\r' || c == '\n')
			return (false);
		if (i > 0 && !isNickChar(nick[i]))
			return (false);
	}
	return (true);
}

void NickCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	if (args.empty())
		return sendError(server, client, ERR_NONICKNAMEGIVEN, "",
			"No nickname given");
	if (args.size()!= 1)
			return sendError(server, client, ERR_ERRONEUSNICKNAME, args[0],
		"Erroneous nickname");

	std::string newNick = args[0];

	if (!isValidNick(newNick))
		return sendError(server, client, ERR_ERRONEUSNICKNAME, newNick,
			"Erroneous nickname");

	Client *other = server.getClientByNick(newNick);
	if (other && other->getFd() != client.getFd())
		return sendError(server, client, ERR_NICKNAMEINUSE, newNick,
			"Nick is already in use");

	if (client.getNickname() == newNick)
		return ;

	client.setNickname(newNick);
	server.tryRegister(client);
}
