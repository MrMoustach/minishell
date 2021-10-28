/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_dup_proto.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:05:07 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/28 14:41:08 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_list	*assign_io(t_list *tokens)
{
	t_list	*tmp;
	t_queue	queue;
	int p[2];
	t_token	*last_command;

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
			last_command = queue.current;
			queue.current->to_close = 0;
			if (!queue.prev)
				queue.current->fds[0] = 0;
			if (!queue.next)
				queue.current->fds[1] = 1;
			else if (queue.next && queue.next->type == PIPE)
			{
				pipe(p);
				queue.current->fds[1] = p[1];
				queue.current->to_close = p[0];
				queue.next->fds[0] = p[0];
				queue.current->in_pipe = 1;
			}
			else if (queue.next && (queue.next->type == REDIRECTION || queue.next->type == APPEND))
			{
				queue.current->fds[0] = 0;
				queue.current->fds[1] = 1;
				if ((queue.next->type == REDIRECTION || queue.next->type == APPEND) && queue.next->direction == LEFT)
					queue.current->fds[0] = create_or_open_file(*(queue.next));
				else
					queue.current->fds[1] = create_or_open_file(*(queue.next));
				if (queue.current->fds[0] < 0 || queue.current->fds[1] < 0)
					g_shell.error = 3;
				queue.current->in_pipe = 1;
			}
		}
		if (queue.current->type == PIPE)
		{
			if (queue.prev->type == REDIRECTION || queue.prev->type == APPEND)
			{
				pipe(p);
				queue.current->fds[0] = p[0];
				queue.current->fds[1] = 1;
				if (queue.prev->direction == LEFT)
					last_command->fds[1] = p[1];
			}
			queue.next->fds[0] = queue.current->fds[0];
			queue.next->fds[1] = queue.current->fds[1];
			queue.next->in_pipe = 1;
		}
		if (queue.current->type == APPEND || queue.current->type == REDIRECTION)
		{
			if (queue.prev->type == APPEND || queue.prev->type == REDIRECTION)
			{
				p[0] = 0;
				if (queue.prev->direction == LEFT)
				{
					if (queue.current->direction == RIGHT)
						last_command->fds[1] = create_or_open_file(*(queue.current));
					else
						p[0] = create_or_open_file(*(queue.current));
				}
				else
				{
					p[0] = create_or_open_file (*(queue.current));
				}
				if (p[0] != 0)
					close (p[0]);
				// TODO: needs to include filename in error handling
				if (last_command->fds[1] < 0 || p[0] < 0)
					g_shell.error = 4;

			}
		}
		if (g_shell.error)
		{
			if (last_command->fds[1] != 1)
				close (last_command->fds[1]);
			if (last_command->fds[0] != 0)
				close (last_command->fds[0]);
			break ;
		}
		queue.prev = queue.current;
		queue.current = queue.next;
		tmp = tmp->next;
	}
	return (tokens);
}