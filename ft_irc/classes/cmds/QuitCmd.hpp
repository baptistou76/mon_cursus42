/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   QuitCmd.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: broboeuf <broboeuf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/20 14:24:59 by broboeuf          #+#    #+#             */
/*   Updated: 2025/11/20 14:33:11 by broboeuf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUITCMD_HPP
# define QUITCMD_HPP

# include "ICommand.hpp"

class QuitCmd : public ICommand
{
    virtual void execute(Server &server, Client &client,
        const std::vector<std::string> &args);
};

#endif

