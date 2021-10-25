/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reparser.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/07 19:09:46 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/25 16:09:22 by iharchi          ###   ########.fr       */
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

	i = 0;
	while ((*token)->str[i])
	{
		if ((*token)->str[i++] != ' ')
			break ;
	}
	if ((*token)->str[i] == '\0')
		return ;
	if (ft_strchr((*token)->str, ' '))
	{
		tab = ft_split((*token)->str, ' ');
		free ((*token)->str);
		(*token)->str = ft_strdup(tab[0]);
		free (tab[0]);
		i = 1;
		while (tab[i])
		{
			(*token)->args = add_to_top_array((*token)->args,
					tab[i++], (*token)->arg_count);
			(*token)->arg_count++;
		}
		free (tab);
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
