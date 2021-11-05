/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 12:33:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/05 09:59:57 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// TODO: Test "exit abcd"
// TODO: Fix number overflow
// TODO: Make ltoa

int	builtin_exit_overflow(char *str) {
	long long	number;
	char		*tmp;
	int			flag;

	flag = 1;
	number = ft_atol(str);
	tmp	   = ft_ltoa(number);
	if (strncmp(str, tmp, ft_strlen(str)))
		flag = 0;	
	free(tmp);
	return (flag);
}

void	builtin_exit(t_token command)
{
	int			exit_code;

	exit_code = 0;
	if (!command.in_pipe)
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
		if (ft_is_number(command.args[0]) && builtin_exit_overflow(command.args[0]))
			exit_code = (int)ft_atol(command.args[0]);
		else
		{
			g_shell.error = 6;
			handle_errors(NULL, command.args[0]);
			exit_code = 255; // FIXED: exit code
		}
	}
	free_tab(g_shell.envp);
	exit (exit_code);
}
