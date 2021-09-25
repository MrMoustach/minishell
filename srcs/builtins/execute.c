/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:28:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/25 10:35:11 by iharchi          ###   ########.fr       */
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
		}
		tmp = tmp->next;
	}
}