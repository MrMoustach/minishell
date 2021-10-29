/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:17:00 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 15:27:06 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_env(t_token command)
{
	int	i;

	i = 0;
	if (command.arg_count)
	{
		g_shell.error = 10;
		handle_errors(&command, "env : Too many arguments\n");
		return (1);
	}
	while (g_shell.envp[i])
	{
		if (ft_strchr(g_shell.envp[i], '='))
			printf("%s\n", g_shell.envp[i]);
		i++;
	}
	return (0);
}
