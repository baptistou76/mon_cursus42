/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   TopicCmd.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/10 17:36:53 by bcaumont          #+#    #+#             */
/*   Updated: 2025/11/12 10:48:33 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOPICCMD_HPP
# define TOPICCMD_HPP

# include "ICommand.hpp"

class TopicCmd : public ICommand
{
  public:
	virtual void execute(Server &server, Client &client,
		const std::vector<std::string> &args);
};

#endif
