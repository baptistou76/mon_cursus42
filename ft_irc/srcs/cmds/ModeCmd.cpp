/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 09:41:02 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 20:51:17 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ModeCmd.hpp"
#include "Utils.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

static bool needsParam(char flag, bool adding)
{
	if (flag == 'k')
		return (adding);
	if (flag == 'l')
		return (adding);
	if (flag == 'o')
		return (true);
	return (false);
}

void ModeCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	if (!client.isRegistered())
		return sendError(server, client, ERR_NOTREGISTERED, "MODE",
			"You have not registered");

	if (args.empty())
		return sendError(server, client, ERR_NEEDMOREPARAMS, "MODE",
			"Not enough parameters");

	std::string channelName = args[0];
	Channel *chan = server.getChannel(channelName);
	if (!chan)
		return sendError(server, client, ERR_NOSUCHCHANNEL, channelName,
			"No such channel");

	if (args.size() == 1)
	{
		std::string modeStr = chan->getMode().getModeString();
		std::string params = channelName + " +" + modeStr;
		return sendReply(server, client, RPL_CHANNELMODEIS, params, "");
	}

	if (!chan->isOperator(client))
		return sendError(server, client, ERR_CHANOPRIVSNEEDED, channelName,
			"You're not channel operator");

	// (le reste de ta logique peut rester identique)
	// ↓ garde ton code existant ici inchangé
	std::string modeFlags = args[1];
	size_t argIndex = 2;
	bool adding = true;
	char flag;
	Client *target;

	std::string appliedFlags;
	std::vector<std::string> appliedParams;

	for (size_t i = 0; i < modeFlags.size(); i++)
	{
		flag = modeFlags[i];
		if (flag == '+')
		{
			adding = true;
			appliedFlags += '+';
			continue ;
		}
		if (flag == '-')
		{
			adding = false;
			appliedFlags += '-';
			continue ;
		}

		if (needsParam(flag, adding))
		{
			if (argIndex >= args.size())
				return sendError(server, client, ERR_NEEDMOREPARAMS,
					"MODE", "Not enough parameters");
		}

		switch (flag)
		{
			case 'i':
				chan->getMode().setInvinteOnly(adding);
				appliedFlags += 'i';
				break;

			case 't':
				chan->getMode().setTopicLocked(adding);
				appliedFlags += 't';
				break;

			case 'k':
				if (adding)
				{
					chan->getMode().setKey(args[argIndex]);
					appliedParams.push_back(args[argIndex]);
					argIndex++;
				}
				else
					chan->getMode().clearKey();
				appliedFlags += 'k';
				break;

			case 'l':
				if (adding)
				{
					chan->getMode().setLimit(
						static_cast<size_t>(atoi(args[argIndex].c_str())));
					appliedParams.push_back(args[argIndex]);
					argIndex++;
				}
				else
					chan->getMode().clearLimit();
				appliedFlags += 'l';
				break;

			case 'o':
				target = server.getClientByNick(args[argIndex]);
				if (!target)
					return sendError(server, client, ERR_NOSUCHNICK,
						args[argIndex], "No such nick");
				if (adding)
					chan->addOperator(target);
				else
					chan->removeOperator(target);
				appliedParams.push_back(args[argIndex]);
				argIndex++;
				appliedFlags += 'o';
				break;

			default:
				sendError(server, client, ERR_UNKNOWNMODE,
					std::string(1, flag), "Unknown mode");
				break;
		}
	}

	if (appliedFlags.empty() || (appliedFlags == "+" || appliedFlags == "-"))
		return ;

	std::string msg = ":" + client.getNickname() + " MODE "
		+ channelName + " " + appliedFlags;

	for (size_t i = 0; i < appliedParams.size(); ++i)
		msg += " " + appliedParams[i];

	chan->broadcast(msg);
}
