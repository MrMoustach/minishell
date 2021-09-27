/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 17:16:10 by zed               #+#    #+#             */
/*   Updated: 2021/09/27 17:37:33 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void init_shell(char	**envp)
{
	g_shell.run = 1;
	g_shell.envp = dup_env(envp);
	g_shell.envp = sort_env(g_shell.envp);
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