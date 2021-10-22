/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expansion.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 10:34:41 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/22 14:35:02 by iharchi          ###   ########.fr       */
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
		if (((t_token *)curr->content)->type != APPEND && ((t_token *)curr->content)->type != LEFT)
			expand_token((t_token *)curr->content);
		curr = curr->next;
	}
	return (tokens);
}
