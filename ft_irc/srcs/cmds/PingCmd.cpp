/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 14:37:53 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 21:02:38 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PingCmd.hpp"
#include "Channel.hpp"
#include "Client.hpp"
#include "Mode.hpp"
#include "Server.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PingCmd::execute(Server &server, Client &client,
	const std::vector<std::string> &args)
{
	std::string token;

	if (!args.empty())
		token = args[0];
	else
		token = server.getName();
	client.sendMessage(":" + server.getName() + " PONG " + 
		server.getName() + " :" + token);
}
