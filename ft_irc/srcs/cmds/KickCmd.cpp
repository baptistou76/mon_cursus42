/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   KickCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:31:57 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 20:52:31 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "KickCmd.hpp"
#include "Server.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void KickCmd::execute(Server &server, Client &client,
					  const std::vector<std::string> &args)
{
	if (!client.isRegistered())
		return sendError(server, client, ERR_NOTREGISTERED, "KICK",
			"You have not registered");

	if (args.size() < 2)
		return sendError(server, client, ERR_NEEDMOREPARAMS, "KICK",
			"Not enough parameters");

	const std::string channelName = args[0];
	const std::string targetNick = args[1];

	Channel *chan = server.getChannel(channelName);
	if (!chan)
		return sendError(server, client, ERR_NOSUCHCHANNEL, channelName,
			"No such channel");

	if (!chan->isMember(client))
		return sendError(server, client, ERR_NOTONCHANNEL, channelName,
			"You're not on that channel");

	if (!chan->isOperator(client))
		return sendError(server, client, ERR_CHANOPRIVSNEEDED, channelName,
			"You're not channel operator");

	Client *victim = server.getClientByNick(targetNick);
	if (!victim)
		return sendError(server, client, ERR_NOSUCHNICK, targetNick,
			"No such nick");

	if (!chan->isMember(*victim))
		return sendError(server, client, ERR_USERNOTINCHANNEL,
			targetNick + " " + channelName, "They aren't on that channel");

	std::string msg = ":" + client.getNickname() + " KICK "
		+ channelName + " " + targetNick;

	chan->broadcast(msg);
	chan->removeMember(victim);
	chan->removeOperator(victim);
}

