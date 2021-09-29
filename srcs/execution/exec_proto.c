/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proto.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 13:34:59 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/29 13:40:18 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	execute_line(t_list	*tokens)
{
	t_list	*tmp;
	t_token	token;

	tmp = tokens;
	while (tmp)
	{
		token = *((t_token *)tmp->content);
		if (token.type == COMMAND)
		{
			builtin_execute(token);
		}
		tmp = tmp->next;
	}
}