/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   CapCmd.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:08:15 by broboeuf          #+#    #+#             */
/*   Updated: 2025/11/20 14:30:40 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CAPCMD_HPP
# define CAPCMD_HPP

#include "ICommand.hpp"

class CapCmd : public ICommand
{
    virtual void execute(Server &serveur, Client &client, 
        const std::vector<std::string> &args);
};

#endif
