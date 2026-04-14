/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 15:39:39 by broboeuf          #+#    #+#             */
/*   Updated: 2025/12/13 08:29:21 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Channel.hpp"
#include "Client.hpp"
#include "QuitCmd.hpp"
#include "Server.hpp"

void QuitCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	Channel	*chan;

	std::string quitMsg = "Client Quit";
	if (!args.empty())
		quitMsg = (args[0][0] == ':' ? args[0].substr(1) : args[0]);
	std::string full = ":" + client.getNickname() + "!" + client.getUsername()
		+ "@localhost QUIT :" + quitMsg;
	const std::map<std::string, Channel *> &chans = server.getChannels();
	for (std::map<std::string,
		Channel *>::const_iterator it = chans.begin(); it != chans.end(); ++it)
	{
		chan = it->second;
		if (chan->isMember(client))
		{
			chan->broadcast(full);
			chan->removeMember(&client);
			chan->removeOperator(&client);
		}
	}
	server.markClientForRemoval(client.getFd());
}
