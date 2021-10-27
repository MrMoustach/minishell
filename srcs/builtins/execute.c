/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:28:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/27 14:44:06 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_builtin(t_token command)
{
	if (!ft_strncmp(command.str, "echo", 5))
		return (1);
	else if (!ft_strncmp(command.str, "pwd", 4))
		return (1);
	else if (!ft_strncmp(command.str, "env", 4))
		return (1);
	else if (!ft_strncmp(command.str, "exit", 5))
		return (1);
	else if (!ft_strncmp(command.str, "export", 7))
		return (1);
	else if (!ft_strncmp(command.str, "unset", 7))
		return (1);
	else if (!ft_strncmp(command.str, "cd", 7))
		return (1);
	return (0);
}

int	builtin_pipe_handler(t_token command)
{
	int	pid;

	if (command.in_pipe)
	{
		pid = fork();
		if (pid == -1)
			perror("fork error");
		else if (pid != 0)
		{
			if (command.fds[0] != 0)
				close (command.fds[0]);
			if (command.fds[1] != 1)
				close (command.fds[1]);
			return (pid);
		}
		if (command.fds[1] != 1)
		{
			dup2(command.fds[1], 1);
			if (command.to_close)
				close (command.to_close);
		}
		if (command.fds[0] != 0)
			dup2(command.fds[0], 0);
	}
	return (pid);
}

void	builtin_execute(t_token command)
{
	if (command.in_pipe && builtin_pipe_handler(command) != 0)
		return ;
	if (!ft_strncmp(command.str, "echo", 5))
		g_shell.exit_code = builtin_echo(command);
	else if (!ft_strncmp(command.str, "pwd", 4))
		g_shell.exit_code = builtin_pwd(command);
	else if (!ft_strncmp(command.str, "env", 4))
		g_shell.exit_code = builtin_env(command);
	else if (!ft_strncmp(command.str, "exit", 5))
		builtin_exit(command);
	else if (!ft_strncmp(command.str, "export", 7))
		g_shell.exit_code = builtin_export(command);
	else if (!ft_strncmp(command.str, "unset", 7))
		g_shell.exit_code = builtin_unset(command);
	else if (!ft_strncmp(command.str, "cd", 7))
		g_shell.exit_code = builtin_cd(command);
	if (command.in_pipe)
		exit (g_shell.exit_code);
}
