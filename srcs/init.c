/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:16:10 by zed               #+#    #+#             */
/*   Updated: 2021/09/29 13:48:50 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell(char	**envp, char **av, int ac)
{
	char	*tmp;
	char	*tmp2;
	int		i;

	g_shell.run = 1;
	g_shell.envp = dup_env(envp);
	g_shell.envp = sort_env(g_shell.envp);
	g_shell.name = ft_strjoin(&av[0][2], "-0.2> ");
	// tmp = ft_getenv("PWD");
	// g_shell.prompt = ft_strjoin(g_shell.name, tmp);
	// free (tmp);
	g_shell.prompt = g_shell.name;
	g_shell.command_status = 0;
	g_shell.debug_mode = 0;
	if (ac > 1)
	{
		i = 0;
		while (av[i])
		{
			if (ft_strncmp(av[i], "-d", 3))
				g_shell.debug_mode = 1;
			i++;
		}
	}
}

void refresh_shell()
{
	char	*cwd;
	char	*tmp;

	tmp = getcwd(tmp, 0);
	if (tmp)
	{
		cwd = ft_strjoin("PWD=", tmp);
		free (tmp);
		ft_modenv("PWD", cwd);
	}
}