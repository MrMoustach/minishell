/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redirect_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:43:58 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 21:33:34 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_queue	init_case_commant(t_queue queue)
{
	queue.last_command = queue.current;
	queue.current->to_close = 0;
	if (!queue.prev)
		queue.current->fds[0] = 0;
	queue.current->fds[1] = 1;
	return (queue);
}

t_queue	assignment_logic(t_queue queue)
{
	queue = case_command(queue);
	queue = case_pipe(queue);
	if (queue.current->type == e_append || queue.current->type == e_redirect)
	{
		queue = case_append_redirect(queue);
	}
	queue.prev = queue.current;
	queue.current = queue.next;
	return (queue);
}
