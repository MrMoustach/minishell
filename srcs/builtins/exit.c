/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:33:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/25 12:58:25 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_exit(t_token command)
{
	int exit_code;
	long long	ret;

	exit_code = 0;
	printf("exit\n");
	if (command.arg_count > 1)
	{
		printf("exit: too many arguments\n");
	}
	if (command.arg_count)
	{
		if (ft_is_number(command.args[0]))
		{
			if (ft_strlen(command.args[0]) < 13)
				ret = ft_atol(command.args[0]);
			else
				ret = 255;
			if (ret >= 2147483647)
				exit_code = (int)((ret - 2147483648) % 255);
			else
				exit_code = (int)(ret) % 255;
		}
		else
			printf("exit: too many arguments\n");
	}
	free_tab(g_shell.envp);
	exit (exit_code);
}