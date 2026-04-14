/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/07 10:11:16 by bcaumont          #+#    #+#             */
/*   Updated: 2026/01/13 14:27:23 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Client.hpp"
#include "Server.hpp"
#include "Topic.hpp"
#include "ft_irc.hpp"
#include "signal.hpp"

int	main(int argc, char **argv)
{
	int	port;

	if (argc != 3)
	{
		std::cerr << "Error: Usage: ./ircserv <port> <password>";
		return (1);
	}
	port = atoi(argv[1]);
	std::string password = argv[2];
	try
	{
		std::signal(SIGINT, sigint_handler);
		Server server(port, password);
		std::cout << "IRC Server starting on port: " << port << std::endl;
		server.run();
	}
	catch (std::exception &e)
	{
		std::cerr << "Error: " << e.what() << std::endl;
		return (1);
	}
	return (0);
}
