/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ICommand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 16:51:25 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/26 21:18:16 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ICOMMAND_HPP
# define ICOMMAND_HPP

# include <string>
# include <vector>

class	Server;
class	Client;

class ICommand
{
  public:
	virtual ~ICommand()
	{
	}
	virtual void execute(Server &server, Client &client,
			const std::vector<std::string> &args) = 0;
};

#endif
