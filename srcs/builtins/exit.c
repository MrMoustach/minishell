/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:33:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/17 10:07:50 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

// TODO: work on exit (task 2)

void	builtin_exit(t_token command)
{
	int exit_code;
	long long	ret;
	// (issam) TODO : fix this case 000000000000000000000000000000000000000000000000012
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
		{
			// DOCS: check this out before pushing
			exit_code = ft_atoi(command.args[0]);
			// if (ft_strlen(command.args[0]) < 13)
			// 	ret = ft_atol(command.args[0]);
			// else
			// 	ret = 255;
			// if (ret >= 2147483647)
			// 	exit_code = (int)((ret - 2147483648) % 255);
			// else
			// 	exit_code = (int)(ret) % 255;
		}
		else
			printf("exit: %s: numeric argument required\n", command.args[0]);
	}
	free_tab(g_shell.envp);
	exit (exit_code);
}