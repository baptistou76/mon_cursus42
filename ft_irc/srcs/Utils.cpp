/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:31:43 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 21:04:02 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Utils.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "ft_irc.hpp"

static std::string getSafeNick(const Client &client)
{
	if (!client.getNickname().empty())
		return client.getNickname();
	return "*";
}

void sendError(Server &server, Client &client, const std::string &code,
			   const std::string &params, const std::string &text)
{
	const std::string nick = getSafeNick(client);
	client.sendMessage(":" + server.getName() + " " + code + " " + nick
		+ (params.empty() ? "" : " " + params)
		+ (text.empty() ? "" : " :" + text));
}

void sendReply(Server &server, Client &client, const std::string &code,
			   const std::string &params, const std::string &text)
{
	const std::string nick = getSafeNick(client);
	client.sendMessage(":" + server.getName() + " " + code + " " + nick
		+ (params.empty() ? "" : " " + params)
		+ (text.empty() ? "" : " :" + text));
}
