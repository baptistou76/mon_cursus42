/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   UserCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/11 10:41:46 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 16:53:56 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "UserCmd.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "Server.hpp"
#include "ft_irc.hpp"

void UserCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	if (client.isRegistered())
		return sendError(server, client, ERR_ALREADYREGISTERED, "USER", 
			"Already registered");
	if (args.size() < 1)
		return sendError(server, client, ERR_NEEDMOREPARAMS, "USER",
			"not enough paramaters");
	
	client.setUsername(args[0]);
	server.tryRegister(client);
}
