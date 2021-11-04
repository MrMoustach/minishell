/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_proto_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:46:35 by omimouni          #+#    #+#             */
/*   Updated: 2021/11/04 15:17:33 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	execute_twice(t_token token)
{
	if (is_builtin(token) && (!ft_strncmp(token.str, "export", 7)
			|| !ft_strncmp(token.str, "unset", 6))
		&& token.arg_count && token.in_pipe)
		return (1);
	return (0);
}

void	execute_line_exit(int stat)
{
	if (WIFEXITED(stat))
		g_shell.exit_code = WEXITSTATUS(stat);
	if (WIFSIGNALED(stat))
	{
		if (WTERMSIG(stat) == SIGINT)
			g_shell.exit_code = 130;
		else if (WTERMSIG(stat) == SIGQUIT)
		{
			g_shell.exit_code = 131;
			g_shell.error = 10;
			handle_errors(NULL, "QUIT\n");
		}
	}
}

void	execute_line_builtin(t_token *token)
{
	if (execute_twice(*token))
	{
		token->in_pipe = 0;
		builtin_execute(*token);
		token->in_pipe = 1;
	}
	if (!is_builtin(*token))
		execute_command(*token);
	else
		builtin_execute(*token);
}

t_list	*next_pipe(t_list *tokens)
{
	t_list	*tmp;
	t_queue	queue;

	tmp = tokens;
	queue = init_queue(&tokens);
	while (tmp)
	{
		if (tmp->next)
			queue.next = ((t_token *)tmp->next->content);
		if (queue.current->type == e_command)
			queue.last_command = queue.current;
		if (queue.current->type == e_pipe)
		{
			queue = handle_pipe(queue);
			break ;
		}
		queue.prev = queue.current;
		queue.current = queue.next;
		tmp = tmp->next;
	}
	return (tokens);
}

void	execute_line(t_list	*tokens)
{
	t_list	*tmp;
	t_token	*token;
	int		stat;

	tmp = tokens;
	while (tmp)
	{
		token = ((t_token *)tmp->content);
		if (token->type == e_command)
		{
			tmp = next_pipe(tmp);
			execute_line_builtin(token);
		}
		else if (token->type == e_append && token->direction == e_left)
			unlink("/tmp/lmao");
		tmp = tmp->next;
	}
	stat = 0;
	g_shell.pid = 5;
	while (waitpid(-1, &stat, 0) > 0)
		execute_line_exit(stat);
	g_shell.pid = 1;
}
