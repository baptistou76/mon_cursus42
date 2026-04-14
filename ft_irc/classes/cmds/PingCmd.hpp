/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PingCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:35:40 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:48:14 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PINGCMD_HPP
# define PINGCMD_HPP

# include "ICommand.hpp"

class PingCmd : public ICommand
{
  public:
	virtual void execute(Server &server, Client &client,
		const std::vector<std::string> &args);
};

#endif
