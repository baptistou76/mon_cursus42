/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PartCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:18:46 by broboeuf          #+#    #+#             */
/*   Updated: 2025/11/20 14:22:20 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARTCMD_HPP
#define PARTCMD_HPP

#include "ICommand.hpp"

class PartCmd : public ICommand
{
    virtual void execute(Server &serveur, Client &client,
        const std::vector<std::string> &args);
};

#endif
