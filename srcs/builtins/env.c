/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:17:00 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/27 12:58:40 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "minishell.h"

void builtin_env(t_token command)
{
	int i;

	i = 0;
	if (command.arg_count)
	{
		printf("env : Too many arguments\n");
		return ;
	}
	while (g_shell.envp[i])
	{
		if (ft_strchr(g_shell.envp[i], '='))
			printf("%s\n", g_shell.envp[i]);
		i++;		
	}
}