/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:34:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/29 15:47:10 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(t_list	*tokens)
{
	t_list	*tmp;
	t_token	token;

	tmp = tokens;
	while (tmp)
	{
		token = *((t_token *)tmp->content);
		if (token.type == COMMAND)
		{
			if (!builtin_execute(token))
				execute_command(token);
		}
		tmp = tmp->next;
	}
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
	int		i;
	
	tmp = ft_strjoin(binary.path, "/");
	path = ft_strjoin(tmp, binary.name);
	free (tmp);

	if (command.arg_count)
		command.args = add_to_top_array(command.args, path, table_count(command.args));
	else
		command.args = add_to_array(command.args, path, 1);
	if ((pid = fork ()) == -1)
	{
		printf("Error: fork error\n");
	}
	else if (pid == 0)
	{
		g_shell.exit_code = execve (path, command.args, g_shell.envp);	
		exit (0);
	}
	wait (NULL);
	free_tab(command.args);
	return (0);
}

int	execute_command(t_token command)
{
	t_binary	binary;

	binary = locate_bin(command.str);
	if (binary.exist)
	{
		execute_binary(binary, command);
	}
	else
		printf("Binary doesnt exist : %s\n", binary.name);
	return (1);
}
