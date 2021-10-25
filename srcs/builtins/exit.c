/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:33:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/25 16:16:38 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

// TODO: work on exit (task 2)

void	builtin_exit(t_token command)
{
	int exit_code;
	long long	ret;

	exit_code = 0;
	printf("exit\n");
	if (command.arg_count > 1)
	{
		printf("exit: too many arguments\n");
		return ;
	}
	if (command.arg_count)
	{
		if (ft_is_number(command.args[0]))
			exit_code = (int)ft_atol(command.args[0]);
		else
			printf("exit: %s: numeric argument required\n", command.args[0]);
	}
	// TODO : free stuff
	free_tab(g_shell.envp);
	exit (exit_code);
}