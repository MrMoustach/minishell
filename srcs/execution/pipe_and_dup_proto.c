/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_dup_proto.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:05:07 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/14 16:34:19 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		create_or_open_file(t_token redirect)
{
	int	fd;
	int	flag;
	
	if (redirect.direction == RIGHT)
	{
		flag = O_CREAT;
		if (redirect.type == APPEND)
			flag =  O_CREAT| O_WRONLY| O_APPEND;
		else
			flag = flag | O_WRONLY | O_TRUNC;
		fd = open(redirect.args[0], flag, 0644);
	}
	else
	{
		if (redirect.type == REDIRECTION)
		{
			fd = open(redirect.args[0], O_RDONLY, 0644);
		}
	}
	return (fd);
}

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
				queue.current->in_pipe = 1;
			}
			else if (queue.next && (queue.next->type == REDIRECTION || queue.next->type == APPEND))
			{
				if (queue.next->type == REDIRECTION && queue.next->direction == LEFT)
					queue.current->fds[0] = create_or_open_file(*(queue.next));
				else
					queue.current->fds[1] = create_or_open_file(*(queue.next));
				printf ("test %d", queue.current->fds[1]);
				// BUG: might not export correctly
				queue.current->in_pipe = 1;
			}
		}
		if (queue.current->type == PIPE)
		{
			queue.next->fds[0] = queue.current->fds[0];
			queue.next->fds[1] = queue.current->fds[1];
			queue.next->in_pipe = 1;
		}
		queue.prev = queue.current;
		queue.current = queue.next;
		tmp = tmp->next;
	}
	return (tokens);
}