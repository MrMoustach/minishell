/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:33:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 17:22:04 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_token command)
{
	int			exit_code;

	exit_code = 0;
	printf("exit\n");
	if (command.arg_count > 1)
	{
		g_shell.exit_code = 1;
		g_shell.error = 10;
		handle_errors(NULL, "exit: too many arguments\n");
		return ;
	}
	if (command.arg_count)
	{
		if (ft_is_number(command.args[0]))
			exit_code = (int)ft_atol(command.args[0]);
		else
		{
			g_shell.error = 6;
			handle_errors(NULL, command.args[0]);
		}
	}
	free_tab(g_shell.envp);
	exit (exit_code);
}
