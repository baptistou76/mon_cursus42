/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   InviteCmd.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:22:28 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/27 22:21:44 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "InviteCmd.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void InviteCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	Client	*target;

	if (!client.isRegistered())
		return (sendError(server, client, ERR_NOTONCHANNEL, "INVITE",
				"You are not registered"));
	if (args.size() < 2)
		return (sendError(server, client, ERR_NEEDMOREPARAMS, "INVITE",
				"Not enough parameters"));
	const std::string nickname = args[0];
	const std::string channelName = args[1];
	chan = server.getChannel(channelName);
	if (!chan)
		return (sendError(server, client, ERR_NOSUCHCHANNEL, channelName,
				"No such channel"));
	target = server.getClientByNick(nickname);
	if (!target)
		return (sendError(server, client, ERR_NOSUCHNICK, nickname,
				"No such nick"));
	if (!chan->isMember(client))
		return (sendError(server, client, ERR_NOTONCHANNEL, channelName,
				"You're not on that channel"));
	if (chan->getMode().isInviteOnly() && !chan->isOperator(client))
		return (sendError(server, client, ERR_CHANOPRIVSNEEDED, channelName,
				"You're not channel operator"));
	if (!chan->isInvited(*target))
		chan->addInvitation(target);
	std::string msg = ":" + client.getNickname() + " INVITE " + nickname + " "
		+ channelName;
	target->sendMessage(msg);
	sendReply(server, client, RPL_INVITING, target->getNickname() + " "
		+ channelName, "");
}
