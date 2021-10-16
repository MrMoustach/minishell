/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/16 18:02:16 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/16 18:05:22 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_last_command(t_token **tmp_token,
	t_list **tokens, t_parser *parser, t_list **list)
{
	(*tmp_token) = create_token((*parser).current->str);
	(*tmp_token)->type = COMMAND;
	list[2] = ft_lstnew((*tmp_token));
	list[2]->next = list[1];
	list[1]->next = list[0]->next;
	free(list[0]);
	parser->last_command = (*tmp_token);
	list[0] = list[1]->next;
	if (!list[3])
		*tokens = list[2];
	else
		list[3]->next = list[2];
}

void
	parser_beofre_command(t_parser *parser, t_list **list)
{
	parser->last_command->arg_count++;
	parser->last_command->args = add_to_array(
			parser->last_command->args, parser->current->str,
			parser->last_command->arg_count);
	list[1]->next = list[0]->next;
	free (list[0]);
	list[0] = list[1]->next;
}

int	parse_switch_arg(t_parser *parser, t_list **list, t_token *tmp_token,
		t_list *tokens)
{
	parser->current = ((t_token *)list[0]->content);
	if (parser->current->type == ARG
		|| (parser->current->type == FILES && parser->context == 2))
	{
		if (!parser->last_command)
		{
			parser_last_command(&tmp_token, &tokens, parser, (t_list **)list);
			return (1);
		}
		if (list[1])
		{
			parser_beofre_command(parser, (t_list **)list);
			return (1);
		}
	}
	return (0);
}
