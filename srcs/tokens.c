/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:45:17 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/27 13:39:53 by iharchi          ###   ########.fr       */
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

int	append_or_redirect(t_token *token)
{
	char	*str;

	str = token->str;
	if (!ft_strncmp(str, ">", ft_strlen(str)))
	{
		token->type = REDIRECTION;
		token->direction = RIGHT;
	}
	else if (!ft_strncmp(str, ">>", ft_strlen(str)))
	{
		token->type = APPEND;
		token->direction = RIGHT;
	}
	else if (!ft_strncmp(str, "<", ft_strlen(str)))
	{
		token->type = REDIRECTION;
		token->direction = LEFT;
	}
	else if (!ft_strncmp(str, "<<", ft_strlen(str)))
	{
		token->type = APPEND;
		token->direction = LEFT;
	}
	else
		return (0);
	return (1);
}

void	tokenizer(t_list *tokens)
{
	int	context;
	t_list	*tmp;
	char *str;
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
		{
			if (context == 0)
			{
				context = 1;
				token->type = COMMAND;
			}
			else if (context == 1)
			{
				token->type = ARG;
			}
			else
			{
				token->type = FILES;
			}
		}
		tmp = tmp->next;
	}
}
