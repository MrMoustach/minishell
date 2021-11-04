/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:34:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/04 19:48:05 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	bin_exist_in_path(t_binary binary)
{
	struct dirent	*dp;
	DIR				*dir;
	int				ret;

	ret = 0;
	dir = opendir(binary.path);
	if (dir)
	{
		while (1)
		{
			dp = readdir(dir);
			if (!dp)
				break ;
			if (!ft_strncmp(binary.name, dp->d_name,
					ft_strlen(binary.name) + 1) && (dp->d_type != DT_DIR))
			{
				ret = 1;
				break ;
			}
		}
		closedir(dir);
	}
	return (ret);
}

char	*get_path(t_binary binary, t_token *command)
{
	char	*path;
	char	*tmp;

	if (binary.exist)
	{
		tmp = ft_strjoin(binary.path, "/");
		path = ft_strjoin(tmp, binary.name);
		free (tmp);
		if (command->arg_count)
			command->args = add_to_top_array(command->args, path,
					table_count(command->args));
		else
			command->args = add_to_array(command->args, path, 1);
		command->arg_count++;
	}
	else
	{
		path = ft_strdup("");
		command->exist = 0;
	}
	return (path);
}

t_queue	handle_pipe(t_queue queue)
{
	pipe (queue.p);
	if (queue.last_command->fds[1] == 1)
	{
		queue.last_command->to_close = queue.p[0];
		queue.last_command->fds[1] = queue.p[1];
	}
	queue.last_command->in_pipe = 1;
	queue.next->in_pipe = 1;
	queue.next->fds[0] = queue.p[0];
	return (queue);
}

int	execute_command(t_token command)
{
	t_binary	binary;

	binary = locate_bin(command.str);
	execute_binary(binary, command);
	if (binary.exist)
		free (binary.path);
	else
	{
		if (command.exist)
		{
			g_shell.error = 11;
			handle_errors(NULL, binary.name);
			g_shell.exit_code = 127;
		}
	}
	free (binary.name);
	return (1);
}
