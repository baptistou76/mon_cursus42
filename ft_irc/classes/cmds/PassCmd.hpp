/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PassCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/12 21:29:33 by broboeuf          #+#    #+#             */
/*   Updated: 2025/11/14 11:42:38 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PASSCMD_HPP
#define PASSCMD_HPP
#include "ICommand.hpp"

class PassCmd : public ICommand 
{
public:
	virtual void execute(Server &server, Client &client,
						 const std::vector<std::string> &args);
};

#endif
