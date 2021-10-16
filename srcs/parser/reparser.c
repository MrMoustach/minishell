/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:09:46 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/17 00:36:05 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/**
 * Potential leak in splits
 */
void
	reparse_command(t_token **token)
{
	int		i;
	char	**tab;

	if (ft_strchr((*token)->str, ' '))
	{
		tab = ft_split((*token)->str, ' ');
		free ((*token)->str);
		(*token)->str = ft_strdup(tab[0]);
		i = 1;
		while (tab[i])
		{
			(*token)->args = add_to_top_array((*token)->args,
					tab[i++], (*token)->arg_count);
			(*token)->arg_count++;
		}
	}
}

void	reparse_commands(t_list	*tokens)
{
	t_list	*tmp;
	t_token	*token;

	tmp = tokens;
	while (tmp)
	{
		token = (t_token *)tmp->content;
		if (token->type == COMMAND)
			reparse_command(&token);
		tmp = tmp->next;
	}
}
