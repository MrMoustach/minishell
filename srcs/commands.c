/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:36:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/03 18:27:05 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_cd(char **args, int argc)
{
	if (argc < 2)
		return (chdir("/home"));
	if (argc > 2)
		return (-2);
	return (chdir(args[0]));
}

int	command_ls(char **args, int argc)
{
	char	*path;
	DIR		*dir;
	struct	dirent *dp;
	
	
	if (argc < 2)
		path = ft_strdup(".");
	else
		path = args[0];
	if (argc > 2)
	{
		//free
		return (-2);
	}
	if ((dir = opendir(path)))
	{
		while ((dp = readdir(dir)))
		{
			if (dp->d_type == 4)
			{
				PRINT(" \e[32m%s\e[39m \n", dp->d_name);
			}
			else
			{
				PRINT(" %s \n", dp->d_name);
			}
			
		}
	}
	else
		return (-3);
	return (0);
		
}