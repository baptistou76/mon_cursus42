/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PrivMsgCmd.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:36:23 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:48:25 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PRIVMSGCMD_HPP
# define PRIVMSGCMD_HPP

# include "ICommand.hpp"

class PrivMsgCmd : public ICommand
{
  public:
	virtual void execute(Server &server, Client &client,
		const std::vector<std::string> &args);
};

#endif
