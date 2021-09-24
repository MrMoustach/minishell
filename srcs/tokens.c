/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:45:17 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/23 17:48:48 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str)
{
	t_token *token;
	
	token = (t_token *)malloc(sizeof(t_token *));
	token->str = str;
	token->empty = 0;
	token->arg_count = 0;
	return (token);
}

void	add_token(t_token *token, t_list **tokens)
{
	ft_lstadd_back(tokens, ft_lstnew(token));
}

// (issam) TODO : Clean up this shit
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
		str = ((t_token *)tmp->content)->str;
		token = ((t_token *)tmp->content);
		if (!ft_strncmp(str, "|", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = PIPE;
			context = 0;
		}
		else if (!ft_strncmp(str, ";", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = END;
			context = 0;
		}
		else if (!ft_strncmp(str, "&&", ft_strlen(str) ))
		{
			((t_token *)tmp->content)->type = RANDOM;
			context = 0;
		}
		else if (!ft_strncmp(str, "||", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = RANDOM;
			context = 0;
		}
		else if (!ft_strncmp(str, "&", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = AND;
			context = 0;
		}
		else if (!ft_strncmp(str, ">", ft_strlen(str)))
		{
			token->type = REDIRECTION;
			token->direction = RIGHT;
			context = 3;
		}
		else if (!ft_strncmp(str, ">>", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = APPEND;
			((t_token *)tmp->content)->direction = RIGHT;
			context = 3;
		}
		else if (!ft_strncmp(str, "<", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = REDIRECTION;
			((t_token *)tmp->content)->direction = LEFT;
			context = 3;
		}
		else if (!ft_strncmp(str, "<<", ft_strlen(str)))
		{
			((t_token *)tmp->content)->type = APPEND;
			((t_token *)tmp->content)->direction = LEFT;
			context = 3;
		}
		else
		{
			if (context == 0)
			{
				context = 1;
				((t_token *)tmp->content)->type = COMMAND;
			}
			else if (context == 1)
			{
				((t_token *)tmp->content)->type = ARG;
			}
			else
			{
				((t_token *)tmp->content)->type = FILES;
			}
		}
		tmp = tmp->next;
	}
}
