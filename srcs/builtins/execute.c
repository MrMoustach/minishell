/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:28:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/29 14:51:26 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_execute(t_token command)
{
	// DOCS : All commands should change the exit status
	if (!ft_strncmp(command.str, "echo", 5))
		builtin_echo(command);
	else if (!ft_strncmp(command.str, "pwd", 4))
		builtin_pwd(command);
	else if (!ft_strncmp(command.str, "env", 4))
		builtin_env(command);
	else if (!ft_strncmp(command.str, "exit", 5))
		builtin_exit(command);
	else if (!ft_strncmp(command.str, "export", 7))
		builtin_export(command);
	else if (!ft_strncmp(command.str, "unset", 7))
		builtin_unset(command);
	else if (!ft_strncmp(command.str, "cd", 7))
		builtin_cd(command);

		
	else if (!ft_strncmp(command.str, "leaks", 6))
		debug_leaks();
	else
		return (0);
	return (1);
}