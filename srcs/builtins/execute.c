/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:28:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/25 12:34:53 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_execute(t_list *tokens)
{
	t_list	*tmp;
	t_token	command;

	tmp = tokens;
	while (tmp)
	{
		command = *((t_token *)tmp->content);
		if (command.type == COMMAND)
		{
			if (!ft_strncmp(command.str, "echo", 5))
				builtin_echo(command);
			if (!ft_strncmp(command.str, "pwd", 4))
				builtin_pwd(command);
			if (!ft_strncmp(command.str, "env", 4))
				builtin_env(command);
			if (!ft_strncmp(command.str, "exit", 5))
				builtin_exit(command);
		}
		tmp = tmp->next;
	}
}