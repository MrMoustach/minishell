/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:45:17 by iharchi           #+#    #+#             */
/*   Updated: 2021/11/03 12:17:13 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str)
{
	t_token	*token;

	token = (t_token *)malloc(sizeof(t_token));
	token->str = str;
	token->empty = 0;
	token->arg_count = 0;
	token->in_pipe = 0;
	token->redirects = 0;
	token->exist = 1;
	return (token);
}

void	free_token(void *t)
{
	t_token	*token;

	token = (t_token *)t;
	free(token->str);
	if (token->arg_count > 0)
		free_tab(token->args);
	free (token);
}

void	add_token(t_token *token, t_list **tokens)
{
	ft_lstadd_back(tokens, ft_lstnew(token));
}
