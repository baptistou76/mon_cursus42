/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   JoinCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:35:58 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:37:13 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef JOINCMD_HPP
# define JOINCMD_HPP

# include "ICommand.hpp"

class JoinCmd : public ICommand
{
  public:
	virtual void execute(Server &server, Client &client,
		const std::vector<std::string> &args);
};

#endif
