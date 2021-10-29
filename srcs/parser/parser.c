/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:04:15 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 21:10:29 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	parser_init(t_parser *parser, t_list **list, t_list **tokens)
{
	list[0] = *tokens;
	list[1] = NULL;
	list[3] = NULL;
	parser->context = 0;
	parser->last_command = NULL;
}

void	parse_files(t_parser *parser, t_list **list)
{
	parser->last_redirect->args = add_to_array(
			parser->last_redirect->args,
			parser->current->str, ++(*parser).last_redirect->arg_count);
	parser->context = 2;
	list[1]->next = list[0]->next;
	free (list[0]->content);
	free (list[0]);
	list[0] = list[1]->next;
}

int	parse_token_type(t_parser *parser, t_list **list)
{
	if (parser->current->type == COMMAND)
	{
		parser->context = 0;
		parser->last_command = parser->current;
	}
	if (parser->current->type == PIPE)
	{
		list[3] = list[0];
		parser->context = 0;
		parser->last_command = NULL;
	}
	if (parser->current->type == REDIRECTION
		|| parser->current->type == APPEND)
	{
		parser->last_redirect = parser->current;
		parser->context = 1;
	}
	if (parser->current->type == FILES && parser->context == 1)
	{
		parse_files(parser, (t_list **)list);
		return (1);
	}
	return (0);
}

t_list	*parse_tokens(t_list *tokens)
{
	t_token		*tmp_token;
	t_parser	parser;
	t_list		*list[4];

	tmp_token = NULL;
	parser_init(&parser, (t_list **)list, &tokens);
	while (list[0])
	{
		if (parse_switch_arg(&parser, (t_list **)list,
				tmp_token, &tokens))
			continue ;
		if (parse_token_type(&parser, (t_list **)list))
			continue ;
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
	if (g_shell.error)
	{
		g_shell.exit_code = 1;
		handle_errors(NULL, NULL);
		return (split.tokens);
	}
	tokenizer(split.tokens);
	syntax = syntax_analysis(split.tokens);
	if (syntax.error)
	{
		g_shell.error = 2;
		g_shell.exit_code = 1;
		handle_errors(&syntax.err_token, NULL);
		return (split.tokens);
	}
	return (parse_tokens(split.tokens));
}
