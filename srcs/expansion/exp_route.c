/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exp_route.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/28 08:06:58 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/29 16:42:11 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	expand_command_token(t_token *command)
{
	char	*tmp;
	int		i;

	tmp = exp_string(command->str);
	free (command->str);
	command->str = tmp;
	i = 0;
	while (i < command->arg_count)
	{
		tmp = exp_string(command->args[i]);
		free(command->args[i]);
		command->args[i] = tmp;
		i++;
	}
}
