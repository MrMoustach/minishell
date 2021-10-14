/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_dup_proto.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:05:07 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/14 13:39:44 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*assign_io(t_list *tokens)
{
	t_list	*tmp;
	t_queue	queue;
	int p[2];

	tmp = tokens;
	queue.current = ((t_token *)(tmp->content));
	queue.prev = NULL;
	queue.next = NULL;
	while (tmp)
	{
		if (tmp->next)
			queue.next = ((t_token *)(tmp->next->content));
		else
			queue.next = NULL;
		if (queue.current->type == COMMAND)
		{
			if (!queue.prev)
				queue.current->fds[0] = 0;
			if (!queue.next)
				queue.current->fds[1] = 1;
			else if (queue.next && queue.next->type == PIPE)
			{
				pipe(p);
				queue.current->fds[1] = p[1];
				queue.next->fds[0] = p[0];
				// sleep (10);
			}
		}
		if (queue.current->type == PIPE)
		{
			queue.next->fds[0] = queue.current->fds[0];
			queue.next->fds[1] = queue.current->fds[1];
		}
		queue.prev = queue.current;
		queue.current = queue.next;
		tmp = tmp->next;
	}
	return (tokens);
}