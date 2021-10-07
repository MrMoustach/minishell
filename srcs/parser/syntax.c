/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   syntax.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 18:24:59 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/07 18:25:19 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_syntax	syntax_analysis(t_list *tokens)
{
	t_syntax	syntax;
	t_list		*tmp;

	tmp = tokens;
	syntax.current = *((t_token *)(tmp->content));
	syntax.prev.empty = 1;
	syntax.error = 0;
	while (tmp)
	{
		if (tmp->next)
			syntax.next = *((t_token *)(tmp->next->content));
		else
			syntax.next.empty = 1;

		if (syntax.current.type == PIPE)
			if (syntax.prev.empty || syntax.next.empty)
			{
				syntax.err_token = syntax.current;
				syntax.error = 1;
				return (syntax);
			}
		if (syntax.current.type == REDIRECTION || syntax.current.type == APPEND)
		{
			if (syntax.next.empty)
			{
				syntax.err_token = syntax.current;
				syntax.error = 2;
				return (syntax);
			}
			if (syntax.next.type != FILES)
			{
				syntax.err_token = syntax.current;
				syntax.error = 3;
				return (syntax);
			}
		}
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