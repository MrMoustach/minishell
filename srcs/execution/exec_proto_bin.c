/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proto_bin.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:54:09 by omimouni          #+#    #+#             */
/*   Updated: 2021/11/03 12:23:44 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	locate_bin_path(t_binary *binary, char *tmp)
{
	int		i;
	char	**paths;

	paths = ft_split(tmp, ':');
	i = 0;
	while (paths[i])
	{
		binary->path = ft_strdup(paths[i]);
		if (bin_exist_in_path(*binary))
		{
			binary->exist = 1;
			break ;
		}
		free (binary->path);
		i++;
	}
	free_tab(paths);
	free (tmp);
}

t_binary	locate_bin(char	*str)
{
	t_binary	binary;
	char		*tmp;

	binary.exist = 0;
	tmp = ft_strrchr(str, '/');
	if (tmp)
	{
		binary.name = ft_strdup(tmp + 1);
		binary.path = ft_substr(str, 0, ft_strlen(str) - ft_strlen(tmp));
		if (bin_exist_in_path(binary))
			binary.exist = 1;
		else
			free (binary.path);
	}
	else
	{
		binary.name = ft_strdup(str);
		binary.path = NULL;
		tmp = ft_getenv("PATH");
		if (!tmp)
			return (binary);
		locate_bin_path(&binary, tmp);
	}
	return (binary);
}

void	execute_bin_child(t_token *command, char *path)
{
	if (command->fds[1] != 1)
	{
		dup2(command->fds[1], 1);
		if (command->to_close)
			close (command->to_close);
	}
	if (command->fds[0] != 0)
		dup2(command->fds[0], 0);
	if (command->exist)
		g_shell.exit_code = execve (path, command->args, g_shell.envp);
	exit (g_shell.exit_code);
}

int	execute_bin_exit(t_token *command, char *path)
{
	free (path);
	if (command->exist)
	{
		if (command->arg_count)
			free (command->args[command->arg_count]);
		else
			free (command->args[0]);
		free(command->args);
	}
	if (command->fds[0] != 0)
		close (command->fds[0]);
	if (command->fds[1] != 1)
		close (command->fds[1]);
	// BUG: wtf???
	if (command->to_close && command->arg_count == 1 && command->exist)
		close (command->to_close);
	return (0);
}

int	execute_binary(t_binary binary, t_token command)
{
	char	*path;
	char	*tmp;
	pid_t	pid;

	if (binary.exist)
	{
		tmp = ft_strjoin(binary.path, "/");
		path = ft_strjoin(tmp, binary.name);
		free (tmp);
		if (command.arg_count)
			command.args = add_to_top_array(command.args, path,
					table_count(command.args));
		else
			command.args = add_to_array(command.args, path, 1);
		command.arg_count++;
	}
	else
	{
		path = ft_strdup("");
		command.exist = 0;
	}
	pid = fork ();
	if (pid == -1)
	{
		g_shell.error = 10;
		handle_errors(NULL, "Error: fork error\n");
	}
	else if (pid == 0)
		execute_bin_child(&command, path);
	return (execute_bin_exit(&command, path));
}
