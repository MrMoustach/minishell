/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:24:59 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/07 19:07:10 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int
	syntax_is_pipe(t_syntax *syntax)
{
	if (syntax->current.type == PIPE)
	{
		if (syntax->prev.empty || syntax->next.empty)
		{
			syntax->err_token = syntax->current;
			syntax->error = 1;
			return (1);
		}
	}
	return (0);
}

int
	syntax_is_arrow(t_syntax *syntax)
{
	if (syntax->current.type == REDIRECTION || syntax->current.type == APPEND)
	{
		if (syntax->next.empty)
		{
			syntax->err_token = syntax->current;
			syntax->error = 2;
			return (1);
		}
		if (syntax->next.type != FILES)
		{
			syntax->err_token = syntax->current;
			syntax->error = 3;
			return (1);
		}
	}
	return (0);
}

void
	syntax_init(t_syntax *syntax, t_list **tmp, t_list *tokens)
{
	*tmp = tokens;
	syntax->current = *((t_token *)((*tmp)->content));
	syntax->prev.empty = 1;
	syntax->error = 0;
}

void
	syntax_is_empty(t_syntax *syntax, t_list *tmp)
{
	if (tmp->next)
		syntax->next = *((t_token *)(tmp->next->content));
	else
		syntax->next.empty = 1;
}

t_syntax
	syntax_analysis(t_list *tokens)
{
	t_syntax	syntax;
	t_list		*tmp;

	syntax_init(&syntax, &tmp, tokens);
	while (tmp)
	{
		syntax_is_empty(&syntax, tmp);
		if (syntax_is_pipe(&syntax))
			return (syntax);
		if (syntax_is_arrow(&syntax))
			return (syntax);
		syntax.prev = syntax.current;
		syntax.current = syntax.next;
		tmp = tmp->next;
	}
	if (g_shell.error != 0)
	{
		syntax.error = 4;
		syntax.err_token = syntax.prev;
	}
	return (syntax);
}
