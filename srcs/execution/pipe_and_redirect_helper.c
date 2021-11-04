/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipe_and_redirect_helper.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/28 17:43:58 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/04 15:04:49 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_queue	init_case_command(t_queue queue)
{
	queue.last_command = queue.current;
	queue.current->to_close = 0;
	if (!queue.prev)
		queue.current->fds[0] = 0;
	queue.current->fds[1] = 1;
	return (queue);
}

t_queue	case_append_redirect_no_command(t_queue queue)
{
	int	fd;

	fd = create_or_open_file(*(queue.current));
	if (fd < 0)
	{
		g_shell.error = 3;
		handle_errors(queue.current, NULL);
		return (queue);
	}
	close (fd);
	return (queue);
}

t_queue	assignment_logic(t_queue queue)
{
	if (queue.current->type == e_command)
		queue = init_case_command(queue);
	if ((queue.current->type == e_append || queue.current->type == e_redirect)
		&& queue.last_command)
		queue = case_append_redirect(queue);
	else if ((queue.current->type == e_append
			|| queue.current->type == e_redirect) && !queue.last_command)
		queue = case_append_redirect_no_command(queue);
	queue.prev = queue.current;
	queue.current = queue.next;
	return (queue);
}
