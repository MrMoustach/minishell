/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:16:10 by zed               #+#    #+#             */
/*   Updated: 2021/09/27 18:47:03 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell(char	**envp, char **av)
{
	char	*tmp;
	char	*tmp2;

	g_shell.run = 1;
	g_shell.envp = dup_env(envp);
	g_shell.envp = sort_env(g_shell.envp);
	g_shell.name = ft_strjoin(&av[0][2], "-0.2> ");
	// tmp = ft_getenv("PWD");
	// g_shell.prompt = ft_strjoin(g_shell.name, tmp);
	// free (tmp);
	g_shell.prompt = g_shell.name;
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