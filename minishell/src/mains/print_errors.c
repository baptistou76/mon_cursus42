/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_errors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bcaumont <bcaumont@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/06/12 23:29:56 by bcaumont          #+#    #+#             */
/*   Updated: 2025/06/14 10:23:34 by bcaumont         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	command_not_found(char *cmd)
{
	ft_putstr_fd(RED "Minishell:~$ " RESET, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED ": Command not found\n" RESET, 2);
}

void	no_such_file_or_directory(char *cmd)
{
	ft_putstr_fd(RED "Minishell:~$ " RESET, 2);
	ft_putstr_fd(cmd, 2);
	ft_putstr_fd(RED ": No such file or directory\n" RED, 2);
}

void	permission_denied(char *file)
{
	ft_putstr_fd(RED "Minishell:~$ ", 2);
	ft_putstr_fd(file, 2);
	ft_putstr_fd(": Permission denied\n" RED, 2);
}

void	error_message(char *str)
{
	ft_putstr_fd(RED "Minishell:~$ " RESET, 2);
	perror(str);
}

void	is_a_directory(char *str)
{
	ft_putstr_fd(RED "Minishell:~$ " RESET, 2);
	ft_putstr_fd(str, 2);
	ft_putstr_fd(RED ": Is a directory\n" RESET, 2);
}
