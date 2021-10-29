/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 14:19:00 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 21:33:34 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	append_or_redirect(t_token *token)
{
	if (!ft_strncmp(token->str, ">", ft_strlen(token->str)))
	{
		token->type = e_redirect;
		token->direction = e_right;
	}
	else if (!ft_strncmp(token->str, ">>", ft_strlen(token->str)))
	{
		token->type = e_append;
		token->direction = e_right;
	}
	else if (!ft_strncmp(token->str, "<", ft_strlen(token->str)))
	{
		token->type = e_redirect;
		token->direction = e_left;
	}
	else if (!ft_strncmp(token->str, "<<", ft_strlen(token->str)))
	{
		token->type = e_append;
		token->direction = e_left;
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
		token->type = e_command;
	}
	else if (context == 1)
		token->type = e_arg;
	else
		token->type = e_files;
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
			token->type = e_pipe;
			context = 0;
		}
		else
			context = command_or_arg(token, context);
		tmp = tmp->next;
	}
}
