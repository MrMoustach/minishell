/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:34:41 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/29 20:31:31 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_token
	*expand_token(t_token *token)
{
	expand_command_token(token);
	return (token);
}

t_list
	*expand_tokens(t_list *tokens)
{
	t_list	*curr;

	curr = tokens;
	while (curr != NULL)
	{
		if (!(((t_token *)curr->content)->type == APPEND
			&& ((t_token *)curr->content)->direction == LEFT))
			expand_token((t_token *)curr->content);
		curr = curr->next;
	}
	return (tokens);
}
