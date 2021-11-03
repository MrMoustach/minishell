/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:34:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/03 12:33:55 by iharchi          ###   ########.fr       */
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
