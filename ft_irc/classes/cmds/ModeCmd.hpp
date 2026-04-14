/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ModeCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:37:08 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:47:47 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MODECMD_HPP
# define MODECMD_HPP

# include "ICommand.hpp"

class ModeCmd : public ICommand
{
  public:
	virtual void execute(Server &server, Client &client,
		const std::vector<std::string> &args);
};

#endif
