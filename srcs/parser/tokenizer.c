/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:19:00 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/27 14:19:20 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_or_redirect(t_token *token)
{
	if (!ft_strncmp(token->str, ">", ft_strlen(token->str)))
	{
		token->type = REDIRECTION;
		token->direction = RIGHT;
	}
	else if (!ft_strncmp(token->str, ">>", ft_strlen(token->str)))
	{
		token->type = APPEND;
		token->direction = RIGHT;
	}
	else if (!ft_strncmp(token->str, "<", ft_strlen(token->str)))
	{
		token->type = REDIRECTION;
		token->direction = LEFT;
	}
	else if (!ft_strncmp(token->str, "<<", ft_strlen(token->str)))
	{
		token->type = APPEND;
		token->direction = LEFT;
	}
	else
		return (0);
	return (1);
}

int	command_or_arg(t_token *token, int context)
{
	if (context == 0)
	{
		context = 1;
		token->type = COMMAND;
	}
	else if (context == 1)
		token->type = ARG;
	else
		token->type = FILES;
	return (context);
}

void	tokenizer(t_list *tokens)
{
	int		context;
	t_list	*tmp;
	char	*str;
	t_token	*token;

	context = 0;
	tmp = tokens;
	while (tmp)
	{
		token = ((t_token *)tmp->content);
		str = token->str;
		if (append_or_redirect(token))
			context = 3;
		else if (!ft_strncmp(str, "|", ft_strlen(str)))
		{
			token->type = PIPE;
			context = 0;
		}
		else
			context = command_or_arg(token, context);
		tmp = tmp->next;
	}
}
