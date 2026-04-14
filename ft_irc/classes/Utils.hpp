/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Utils.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 18:29:22 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/20 21:01:27 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef UTILS_HPP
#define UTILS_HPP

#include <string>

class Server;
class Client;

void sendError(Server &server, Client &client, const std::string &code,
               const std::string &params, const std::string &text);

void sendReply(Server &server, Client &client, const std::string &code,
               const std::string &params, const std::string &text);

#endif
