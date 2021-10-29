/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:03:01 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 20:25:10 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	debug_mode(char **av, int ac)
{
	int	i;
	// TODO: delete this for prod
	if (ac > 1)
	{
		i = 1;
		while (av[i])
		{
			if (!ft_strncmp(av[i], "-d", 3))
			{
				g_shell.debug_mode = 1;
				if (av[i + 1])
					g_shell.debug_mode = ft_atoi(av[i + 1]);
			}
			i++;
		}
	}
	if (g_shell.debug_mode)
		printf("\e[41m!!Verbose debug mode level %d enabled!!\e[49m\n",
			g_shell.debug_mode);
}

void	init_shell(char	**envp, char **av, int ac)
{
	g_shell.run = 1;
	g_shell.error = 0;
	g_shell.envp = dup_env(envp);
	g_shell.envp = sort_env(g_shell.envp);
	g_shell.name = ft_strjoin(&av[0][2], "-0.9> ");
	g_shell.prompt = g_shell.name;
	g_shell.command_status = 0;
	g_shell.debug_mode = 0;
	g_shell.exit_code = 0;
	debug_mode(av, ac);
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
