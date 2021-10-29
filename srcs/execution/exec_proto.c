/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:34:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 17:23:05 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_twice(t_token token)
{
	if (is_builtin(token) && (!ft_strncmp(token.str, "export", 7) ||
		!ft_strncmp(token.str, "unset", 6)) && token.arg_count && token.in_pipe)
		return (1);
	return (0);
}

void	execute_line(t_list	*tokens)
{
	t_list	*tmp;
	t_token	token;
	int		stat;

	tmp = tokens;
	while (tmp)
	{
		token = *((t_token *)tmp->content);
		if (token.type == COMMAND)
		{
			if(execute_twice(token))
			{
				token.in_pipe = 0;
				builtin_execute(token);
				token.in_pipe = 1;
			}
			if (!is_builtin(token))
				execute_command(token);
			else
				builtin_execute(token);
		}
		else if (token.type == APPEND && token.direction == LEFT)
				unlink("/tmp/lmao");
		tmp = tmp->next;
	}
	stat = 0;
	g_shell.pid = 5;
	while (waitpid(-1, &stat, 0) > 0)
	{
		if (WIFEXITED(stat))
			g_shell.exit_code = WEXITSTATUS(stat);
		if (WIFSIGNALED(stat))
		{
			if (WTERMSIG(stat) == SIGINT)
				g_shell.exit_code = 130;
			else if (WTERMSIG(stat) == SIGQUIT)
			{
				g_shell.exit_code = 131;
				g_shell.error = 10;
				handle_errors(NULL, "QUIT\n");
			}
		}
	}
	g_shell.pid = 1;
}

int			bin_exist_in_path(t_binary binary)
{
	struct dirent	*dp;
	DIR				*dir;
	int				ret;

	ret = 0;
	if ((dir = opendir(binary.path)))
	{
		while ((dp = readdir(dir)))
			if (!ft_strncmp(binary.name, dp->d_name, ft_strlen(binary.name) + 1) && (dp->d_type != DT_DIR))
			{
				ret = 1;
				break ;	
			}
		closedir(dir);
	}
	return (ret);
}

t_binary	locate_bin(char	*str)
{
	t_binary	binary;
	char		*tmp;
	char		**paths;
	int			i;
	
	binary.exist = 0;
	if ((tmp = ft_strrchr(str, '/')))
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
		paths = ft_split(tmp, ':');
		i = 0;
		while (paths[i])
		{
			binary.path = ft_strdup(paths[i]);
			if (bin_exist_in_path(binary))
			{
				binary.exist = 1;	
				break ;
			}
			free (binary.path);
			i++;
		}
		free_tab(paths);
		free (tmp);
	}
	return (binary);
}

int	execute_binary(t_binary binary, t_token command)
{
	char	*path;
	char	*tmp;
	pid_t	pid;
	
	tmp = ft_strjoin(binary.path, "/");
	path = ft_strjoin(tmp, binary.name);
	free (tmp);
	if (command.arg_count)
		command.args = add_to_top_array(command.args, path, table_count(command.args));
	else
		command.args = add_to_array(command.args, path, 1);
	command.arg_count++;
	if ((pid = fork ()) == -1)
	{
		g_shell.error = 10;
		handle_errors(NULL, "Error: fork error\n");
	}
	else if (pid == 0)
	{
		if (command.fds[1] != 1)
		{
			dup2(command.fds[1], 1);
			if (command.to_close)
				close (command.to_close);
		}
		if (command.fds[0] != 0)
			dup2(command.fds[0], 0);
		g_shell.exit_code = execve (path, command.args, g_shell.envp);
		exit (g_shell.exit_code);
	}
	free (path);
	if (command.arg_count)
		free (command.args[command.arg_count]);
	else
		free (command.args[0]);
	free(command.args);
	if (command.fds[0] != 0)
		close (command.fds[0]);	
	if (command.fds[1] != 1)
		close (command.fds[1]);	
	return (0);
}

int	execute_command(t_token command)
{
	t_binary	binary;

	binary = locate_bin(command.str);
	if (binary.exist)
	{
		execute_binary(binary, command);
		free (binary.path);
	}
	else
	{
		g_shell.exit_code = 127;
		g_shell.error = 11;
		handle_errors(NULL, binary.name);
	}
	free (binary.name);
	return (1);
}
