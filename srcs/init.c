/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:03:01 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/04 15:49:45 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_shell(char	**envp)
{
	g_shell.run = 1;
	g_shell.error = 0;
	g_shell.envp = dup_env(envp);
	g_shell.envp = sort_env(g_shell.envp);
	g_shell.name = ft_strjoin("minishell", "-1.0> ");
	g_shell.prompt = g_shell.name;
	g_shell.command_status = 0;
	g_shell.debug_mode = 0;
	g_shell.exit_code = 0;
}

void	refresh_shell(void)
{
	char	*cwd;
	char	*tmp;

	tmp = NULL;
	tmp = getcwd(tmp, 0);
	g_shell.error = 0;
	g_shell.last_status = g_shell.exit_code;
	g_shell.exit_code = 0;
	if (tmp)
	{
		cwd = ft_strjoin("PWD=", tmp);
		free (tmp);
		ft_modenv("PWD", cwd);
	}
	unlink("/tmp/lmao");
}

void	clean_shell(t_list *tokens, char *line)
{
	ft_lstclear(&tokens, free_token);
	free(line);
	refresh_shell();
}
