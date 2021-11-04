/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redirect.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/30 13:05:07 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/04 13:32:58 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_queue	pipe_after_command(t_queue queue)
{
	if (queue.next && queue.next->type == e_pipe)
	{
		pipe(queue.p);
		queue.current->fds[1] = queue.p[1];
		queue.current->to_close = queue.p[0];
		queue.next->fds[0] = queue.p[0];
		queue.current->in_pipe = 1;
	}
	return (queue);
}

t_queue	case_command(t_queue queue)
{
	if (queue.current->type == e_command)
	{
		queue = init_case_command(queue);
		// queue = pipe_after_command(queue);
		if (queue.next
			&& (queue.next->type == e_redirect || queue.next->type == e_append))
		{
			if ((queue.next->type == e_redirect || queue.next->type == e_append)
				&& queue.next->direction == e_left)
				queue.current->fds[0] = create_or_open_file(*(queue.next));
			else
				queue.current->fds[1] = create_or_open_file(*(queue.next));
			if (queue.current->fds[0] < 0 || queue.current->fds[1] < 0)
			{
				g_shell.error = 3;
				handle_errors(queue.next, NULL);
			}
			queue.current->in_pipe = 1;
		}
	}
	return (queue);
}

t_queue	case_pipe(t_queue queue)
{
	//BUG: < file | rev segfault
	if (queue.current->type == e_pipe)
	{
		if (queue.prev->type == e_redirect || queue.prev->type == e_append)
		{
			pipe(queue.p);
			queue.current->fds[0] = queue.p[0];
			queue.current->fds[1] = 1;
			if (queue.prev->direction == e_left && queue.last_command)
			{
				queue.last_command->fds[1] = queue.p[1];
				queue.last_command->to_close = queue.p[0];
			}
		}
		queue.next->fds[0] = queue.current->fds[0];
		// queue.next->fds[1] = queue.current->fds[1];
		queue.next->in_pipe = 1;
	}
	return (queue);
}

t_queue	case_append_redirect(t_queue queue)
{
	if ((queue.prev->type == e_append || queue.prev->type == e_redirect))
	{
		queue.p[0] = 0;
		if (queue.prev->direction == e_left)
		{
			if (queue.current->direction == e_right)
				queue.last_command->fds[1]
					= create_or_open_file(*(queue.current));
			else
				queue.p[0] = create_or_open_file(*(queue.current));
		}
		else
		{
			queue.p[0] = create_or_open_file (*(queue.current));
		}
		if (queue.p[0] != 0)
			close (queue.p[0]);
		if (queue.last_command->fds[1] < 0 || queue.p[0] < 0)
		{
			g_shell.error = 3;
			handle_errors(queue.current, NULL);
		}
	}
	return (queue);
}

t_list	*assign_io(t_list *tokens)
{
	t_list	*tmp;
	t_queue	queue;
	t_token	*token;
	t_list	*tmp2;

	tmp = tokens;
	queue.prev = NULL;
	queue.next = NULL;
	queue.last_command = NULL;
	queue.current = ((t_token *)(tmp->content));
	if (queue.current->type != e_command)
	{
		token = create_token(ft_strdup("lmao"));
		token->exist = 0; 
		token->type = e_command; 
		tmp2 = ft_lstnew(token);
		tmp2->next = tokens;
		tokens = tmp2;
		tmp = tokens;
	}
	queue.current = ((t_token *)(tmp->content));
	while (tmp)
	{
		if (tmp->next)
			queue.next = ((t_token *)(tmp->next->content));
		else
			queue.next = NULL;
		queue = assignment_logic(queue);
		if (g_shell.error && queue.last_command)
		{
			if (queue.last_command->fds[1] != 1)
				close (queue.last_command->fds[1]);
			if (queue.last_command->fds[0] != 0)
				close (queue.last_command->fds[0]);
			break ;
		}
		tmp = tmp->next;
	}
	return (tokens);
}
