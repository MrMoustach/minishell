/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:31:46 by zed               #+#    #+#             */
/*   Updated: 2021/10/16 17:12:48 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"



void	parser_last_command(t_token **tmp_token,
	t_list **tokens, t_parser *parser, t_list ***list)
{
	(*tmp_token) = create_token((*parser).current->str);
	(*tmp_token)->type = COMMAND;
	(*list)[2] = ft_lstnew((*tmp_token));
	(*list)[2]->next = (*list)[1];
	(*list)[1]->next = (*list)[0]->next;
	free((*list)[0]);
	parser->last_command = (*tmp_token);
	(*list)[0] = (*list)[1]->next;
	if (!(*list)[3])
		*tokens = (*list)[2];
	else
		(*list)[3]->next = (*list)[2];
}

void
	parser_init(t_list ***list, t_list **tokens, t_parser *parser)
{
	// (*list)[0] = (*tokens);
	// (*list)[1] = NULL;
	parser->context = 0;
	parser->last_command = NULL;
	// (*list)[3] = NULL;
}

/**
* 0 tmp
* 1 before
* 2 tmp_lst;
* 3 last_assignable_token
*/

t_list	*parse_tokens(t_list *tokens)
{
	t_token		*tmp_token;
	t_parser	parser;
	t_list		*list[4];

	list[0] = tokens;
	list[1] = NULL;
	list[3] = NULL;
	parser_init(((t_list ***)(&list)), &tokens, &parser);
	while (list[0])
	{
		parser.current = ((t_token *)list[0]->content);
		if (parser.current->type == ARG
			|| (parser.current->type == FILES && parser.context == 2))
		{
			if (!parser.last_command)
			{
				parser_last_command(&tmp_token, &tokens, &parser,
						((t_list ***)(&list)));
				continue ;
			}
			if (list[1])
			{
				parser.last_command->arg_count++;
				parser.last_command->args = add_to_array(
						parser.last_command->args, parser.current->str,
						parser.last_command->arg_count);
				list[1]->next = list[0]->next;
				free (list[0]);
				list[0] = list[1]->next;
				continue ;
			}
		}
		if (parser.current->type == COMMAND)
		{
			parser.context = 0;
			parser.last_command = parser.current;
		}
		if (parser.current->type == PIPE || parser.current->type == RANDOM)
		{
			list[3] = list[0];
			parser.context = 0;
			parser.last_command = NULL;
		}
		if (parser.current->type == REDIRECTION
			|| parser.current->type == APPEND)
		{
			parser.last_redirect = parser.current;
			parser.context = 1;
		}
		if (parser.current->type == FILES && parser.context == 1)
		{
			parser.last_redirect->args = add_to_array(
					parser.last_redirect->args,
					parser.current->str, ++parser.last_redirect->arg_count);
			parser.context = 2;
			list[1]->next = list[0]->next;
			free (list[0]);
			list[0] = list[1]->next;
			continue ;
		}
		list[1] = list[0];
		list[0] = list[0]->next;
	}
	return (tokens);
}

t_list	*parser(char	*line)
{
	t_spliter	split;
	t_syntax	syntax;

	split = spliter(line);
	tokenizer(split.tokens);
	syntax = syntax_analysis(split.tokens);
	if (syntax.error)
	{
		printf("syntax error m8 code : %d near %s\n",
			syntax.error, syntax.err_token.str);
		g_shell.error = 2;
		return (split.tokens);
	}
	return (parse_tokens(split.tokens));
}
