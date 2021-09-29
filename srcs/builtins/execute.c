/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:28:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/29 13:39:13 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_execute(t_token command)
{
		// DOCS : All commands should change the exit status
		if (command.type == COMMAND)
		{
			if (!ft_strncmp(command.str, "echo", 5))
				builtin_echo(command);
			if (!ft_strncmp(command.str, "pwd", 4))
				builtin_pwd(command);
			if (!ft_strncmp(command.str, "env", 4))
				builtin_env(command);
			if (!ft_strncmp(command.str, "exit", 5))
				builtin_exit(command);
			if (!ft_strncmp(command.str, "export", 7))
				builtin_export(command);
			if (!ft_strncmp(command.str, "unset", 7))
				builtin_unset(command);
			if (!ft_strncmp(command.str, "cd", 7))
				builtin_cd(command);

				
			if (!ft_strncmp(command.str, "leaks", 6))
				debug_leaks();
		}
}