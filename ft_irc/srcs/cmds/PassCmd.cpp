/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:30:44 by broboeuf          #+#    #+#             */
/*   Updated: 2025/11/20 20:53:45 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PassCmd.hpp"
#include "Server.hpp"
#include "Client.hpp"
#include "Utils.hpp"
#include "ft_irc.hpp"

void PassCmd::execute(Server &server, Client &client,
                      const std::vector<std::string> &args)
{
    if (client.isRegistered())
        return sendError(server, client, ERR_ALREADYREGISTERED, "PASS",
                         "Already registered");

    if (args.empty())
        return sendError(server, client, ERR_NEEDMOREPARAMS, "PASS",
                         "Not enough parameters");

    const std::string &pwd = args[0];

    if (pwd != server.getPassword())
        return sendError(server, client, ERR_PASSWDMISMATCH, "",
                         "Password incorrect");

    client.setPassOk(true);
    server.tryRegister(client);
}
