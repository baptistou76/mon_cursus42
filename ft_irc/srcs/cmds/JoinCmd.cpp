/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 08:36:51 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/28 22:17:43 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "JoinCmd.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Topic.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

static bool isValidChannelName(const std::string &name)
{
	if (name.empty() || name[0] != '#')
		return (false);
	if (name.size() > 50)
		return (false);
	for (size_t i = 0; i < name.size(); ++i)
	{
		unsigned char c = name[i];
		if (c < 0x20 || c == 0x7F)
			return (false);
		if (c == ' ' || c == ',' || c == ':' || c == '\r' || c == '\n')
			return (false);
	}
	return (true);
}

void JoinCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;
	bool	isNewChannel;
	Client	*c;

	if (!client.isRegistered())
		return (sendError(server, client, ERR_NOTREGISTERED, "JOIN",
				"You have not registered"));

	if (args.empty())
		return (sendError(server, client, ERR_NEEDMOREPARAMS, "JOIN",
				"Not enough parameters"));

	std::string chanName = args[0];
	std::string key = (args.size() > 1) ? args[1] : "";

	if (!isValidChannelName(chanName))
		return (sendError(server, client, ERR_BADCHANMASK, chanName,
				"Bad Channel Mask"));

	chan = server.getChannel(chanName);
	isNewChannel = false;
	if (!chan)
	{
		chan = server.createChannel(chanName);
		isNewChannel = true;
	}

	Mode &mode = chan->getMode();

	if (mode.isInviteOnly() && !chan->isMember(client)
		&& !chan->isInvited(client))
		return (sendError(server, client, ERR_INVITEONLYCHAN, chanName,
				"Channel is invite-only"));

	if (mode.hasKey() && !mode.checkKey(key))
		return (sendError(server, client, ERR_BADCHANNELKEY, chanName,
				"Incorrect channel key"));

	if (mode.hasLimit() && chan->getMemberCount() >= mode.getLimit())
		return (sendError(server, client, ERR_CHANNELISFULL, chanName,
				"Channel is full"));

	if (chan->isMember(client))
		return ;

	chan->addMember(&client);

	if (isNewChannel)
		chan->addOperator(&client);

	if (chan->isInvited(client))
		chan->removeInvitation(&client);

	std::string joinMsg = ":" + client.getNickname() + " JOIN " + chanName;
	chan->broadcast(joinMsg);

	if (!chan->getTopic().getTopic().empty())
		sendReply(server, client, RPL_TOPIC, chanName,
			chan->getTopic().getTopic());
	else
		sendReply(server, client, RPL_NOTOPIC, chanName, "No topic is set");

	std::string names;
	std::set<Client *> members = chan->getMembers();
	std::set<Client *>::iterator it = members.begin();
	while (it != members.end())
	{
		c = *it;
		if (chan->isOperator(*c))
			names += "@" + c->getNickname() + " ";
		else
			names += c->getNickname() + " ";
		++it;
	}
	sendReply(server, client, RPL_NAMREPLY, "= " + chanName, names);
	sendReply(server, client, RPL_ENDOFNAMES, chanName, "End of NAMES list");
}
