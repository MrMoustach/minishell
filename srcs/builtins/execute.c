/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:28:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/01 15:05:01 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_execute(t_token command)
{
	int	ret;
	int	p[2];

	ret = 1;
	if (command.fds[1] != 1)
	{
		p[1] = dup(1);
		dup2(command.fds[1], 1);
		close (command.fds[1] - 1);
	}
	if (command.fds[0] != 0)
	{
		p[0] = dup(0);
		dup2(command.fds[0], 0);
	}
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
		ret = 0;
	if (command.fds[0] != 0)
	{
		dup2(0, p[0]);
		close (command.fds[0]);	
	}
	if (command.fds[1] != 1)
	{
		dup2(1, p[1]);		
		close (command.fds[1]);	
	}
	return (ret);
}