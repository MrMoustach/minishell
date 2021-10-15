/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:31:46 by zed               #+#    #+#             */
/*   Updated: 2021/10/15 17:39:57 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// TODO : cleanup priority N1

// t_list	*parser(char	*line)
// {
// 	t_spliter	split;
// 	t_syntax	syntax;
// 	t_parser	parser;
// 	t_list		*tmp;
// 	t_list		*before;
// 	t_token		*tmp_token;
// 	t_list		*tmp_lst;
// 	t_list		*last_assignable_token;

// 	split = spliter(line);
// 	tokenizer(split.tokens);
// 	syntax = syntax_analysis(split.tokens);
// 	if (syntax.error)
// 	{
// 		printf("syntax error m8 code : %d near %s\n", syntax.error, syntax.err_token.str);
// 		g_shell.error = 2;
// 		return (split.tokens);
// 	}
// 	tmp = split.tokens;
// 	before = NULL;
// 	parser.context = 0;
// 	parser.last_command = NULL;
// 	last_assignable_token = NULL;
// 	while (tmp)
// 	{
// 		parser.current = ((t_token *)tmp->content);
// 		if (parser.current->type == ARG || (parser.current->type == FILES && parser.context == 2))
// 		{
// 			if (!parser.last_command)
// 			{
// 				tmp_token = create_token(parser.current->str);
// 				tmp_token->type = COMMAND;
// 				tmp_lst = ft_lstnew(tmp_token);
// 				tmp_lst->next = before;
// 				before->next = tmp->next;
// 				free(tmp);
// 				parser.last_command = tmp_token;
// 				tmp = before->next;
// 				if (!last_assignable_token)
// 					split.tokens = tmp_lst;
// 				else
// 					last_assignable_token->next = tmp_lst;
// 				continue ;
// 			}
// 			if (before)
// 			{
// 				parser.last_command->arg_count++;
// 				parser.last_command->args = add_to_array(parser.last_command->args, parser.current->str, parser.last_command->arg_count);
// 				before->next = tmp->next;
// 				free (tmp);
// 				tmp = before->next;
// 				continue ;
// 			}
// 		}
// 		if (parser.current->type == COMMAND)
// 		{
// 			parser.context = 0;
// 			parser.last_command = parser.current;
// 		}
// 		if (parser.current->type == PIPE || parser.current->type == RANDOM)
// 		{
// 			last_assignable_token = tmp;
// 			parser.context = 0;
// 			parser.last_command = NULL;
// 		}
// 		if (parser.current->type == REDIRECTION || parser.current->type == APPEND)
// 		{
// 			parser.last_redirect = parser.current;
// 			parser.context = 1;
// 		}
// 		if (parser.current->type == FILES && parser.context == 1)
// 		{
// 			// parser.last_redirect->args = malloc(sizeof(char *) * 2);
// 			// parser.last_redirect->args[0] = parser.current->str;
// 			// parser.last_redirect->args[1] = NULL;
// 			// parser.last_redirect->arg_count++;
// 			parser.last_redirect->args = add_to_array(parser.last_redirect->args, parser.current->str, ++parser.last_redirect->arg_count);
// 			parser.context = 2;
// 			before->next = tmp->next;
// 			free (tmp);
// 			tmp = before->next;
// 			continue ;
// 		}
// 		before = tmp;
// 		tmp = tmp->next;
// 	}
// 	return (split.tokens);
// }

t_list	*parse_tokens(t_list *tokens)
{
	t_list		*tmp;
	t_list		*before;
	t_token		*tmp_token;
	t_list		*tmp_lst;
	t_list		*last_assignable_token;
	t_parser	parser;
	
	tmp = tokens;
	before = NULL;
	parser.context = 0;
	parser.last_command = NULL;
	last_assignable_token = NULL;
	while (tmp)
	{
		parser.current = ((t_token *)tmp->content);
		if (parser.current->type == ARG || (parser.current->type == FILES && parser.context == 2))
		{
			if (!parser.last_command)
			{
				tmp_token = create_token(parser.current->str);
				tmp_token->type = COMMAND;
				tmp_lst = ft_lstnew(tmp_token);
				tmp_lst->next = before;
				before->next = tmp->next;
				free(tmp);
				parser.last_command = tmp_token;
				tmp = before->next;
				if (!last_assignable_token)
					tokens = tmp_lst;
				else
					last_assignable_token->next = tmp_lst;
				continue ;
			}
			if (before)
			{
				parser.last_command->arg_count++;
				parser.last_command->args = add_to_array(parser.last_command->args, parser.current->str, parser.last_command->arg_count);
				before->next = tmp->next;
				free (tmp);
				tmp = before->next;
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
			last_assignable_token = tmp;
			parser.context = 0;
			parser.last_command = NULL;
		}
		if (parser.current->type == REDIRECTION || parser.current->type == APPEND)
		{
			parser.last_redirect = parser.current;
			parser.context = 1;
		}
		if (parser.current->type == FILES && parser.context == 1)
		{
			parser.last_redirect->args = add_to_array(parser.last_redirect->args, parser.current->str, ++parser.last_redirect->arg_count);
			parser.context = 2;
			before->next = tmp->next;
			free (tmp);
			tmp = before->next;
			continue ;
		}
		before = tmp;
		tmp = tmp->next;
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
		printf("syntax error m8 code : %d near %s\n", syntax.error, syntax.err_token.str);
		g_shell.error = 2;
		return (split.tokens);
	}
	return (parse_tokens(split.tokens));
}
