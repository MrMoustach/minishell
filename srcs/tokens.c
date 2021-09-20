/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 16:45:17 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/20 07:58:17 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_token	*create_token(char *str)
{
	t_token *token;
	
	token = (t_token *)malloc(sizeof(t_token *));
	token->str = str;
	return (token);
}

void	add_token(t_token *token, t_list **tokens)
{
	ft_lstadd_back(tokens, ft_lstnew(token));
}