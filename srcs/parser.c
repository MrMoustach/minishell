/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 16:31:46 by zed               #+#    #+#             */
/*   Updated: 2021/09/23 17:12:33 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_syntax	syntax_analysis(t_list *tokens)
{
	t_syntax	syntax;
	t_list		*tmp;

	tmp = tokens;
	syntax.current = *((t_token *)(tmp->content));
	syntax.prev.empty = 1;
	syntax.error = 0;
	while (tmp)
	{
		if (tmp->next)
			syntax.next = *((t_token *)(tmp->next->content));
		else
			syntax.next.empty = 1;

		if (syntax.current.type == PIPE)
			if (syntax.prev.empty || syntax.next.empty)
			{
				syntax.err_token = syntax.current;
				syntax.error = 1;
				return (syntax);
			}
		if (syntax.current.type == REDIRECTION || syntax.current.type == APPEND)
		{
			if (syntax.next.empty)
			{
				syntax.err_token = syntax.current;
				syntax.error = 2;
				return (syntax);
			}
			if (syntax.next.type != FILES)
			{
				syntax.err_token = syntax.current;
				syntax.error = 3;
				return (syntax);
			}
		}
		syntax.prev = syntax.current;
		syntax.current = syntax.next;
		tmp = tmp->next;
	}
	return (syntax);
}

char	**add_to_array(char **array, char *str, int count)
{
	char	**tmp;
	int		i;
	
	tmp = malloc(sizeof(char *) * (count + 1));
	i = 0;
	while (i < count - 1)
	{
		tmp[i] = array[i];
		i++;
	}
	tmp[i++] = str;
	tmp[i] = NULL;
	if (count != 1)
		free (array);
	return (tmp);
}

void	parser(char	*line)
{
	t_spliter	split;
	t_syntax	syntax;
	t_parser	parser;
	t_list		*tmp;
	t_list		*before;
	t_token		token;
	t_token		*tmp_token;
	t_list		*tmp_lst;
	int			i;

	split = spliter(line);
	tokenizer(split.tokens);
	syntax = syntax_analysis(split.tokens);
	if (syntax.error)
	{
		printf("syntax error m8 code : %d near %s\n", syntax.error, syntax.err_token.str);
		return ;
	}
	tmp = split.tokens;
	before = NULL;
	parser.context = 0;
	parser.last_command = NULL;
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
				split.tokens = tmp_lst;
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
			parser.context = 0;
		if (parser.current->type == REDIRECTION || parser.current->type == APPEND)
		{
			parser.last_redirect = parser.current;
			parser.context = 1;
		}
		if (parser.current->type == FILES && parser.context == 1)
		{
			// parser.last_redirect->output = parser.current->str;
			parser.last_redirect->args = malloc(sizeof(char *) * 2);
			parser.last_redirect->args[0] = parser.current->str;
			parser.last_redirect->args[1] = NULL;
			parser.last_redirect->arg_count++;
			parser.context = 2;
			before->next = tmp->next;
			free (tmp);
			tmp = before->next;
			continue ;
		}
		// if (parser.current->type == FILES && parser.context == 2)
		// {
		// 	if (!parser.last_command)
		// 	{
		// 		tmp_token = create_token(parser.current->str);
		// 		tmp_token->type = COMMAND;
		// 		tmp_lst = ft_lstnew(tmp_token);
		// 		tmp_lst->next = before;
		// 		before->next = tmp->next;
		// 		free(tmp);
		// 		parser.last_command = tmp_token;
		// 		tmp = before->next;
		// 		split.tokens = tmp_lst;
		// 		continue ;
		// 	}
		// 	else
		// 	{
		// 		parser.last_command->arg_count++;
		// 		parser.last_command->args = add_to_array(parser.last_command->args, parser.current->str, parser.last_command->arg_count);
		// 		before->next = tmp->next;
		// 		free (tmp);
		// 		tmp = before->next;
		// 		continue ;
		// 	}
		// 	before->next = tmp->next;
		// 	free (tmp);
		// 	tmp = before->next;
		// 	continue ;
		// }
		before = tmp;
		tmp = tmp->next;
	}
	tmp = split.tokens;
	while (tmp)
	{
		token = *((t_token *)tmp->content);
		printf("TOKEN : %s\n", token.str);
		printf("TYPE : ");
		printf("%s\n", types[(int)token.type]);
		if (token.arg_count > 0 && token.type == COMMAND)
		{
			i = 0;
			printf("args : ");
			while (i < token.arg_count)
				printf("%s ", token.args[i++]);
			printf("\n");
		}
		if ((token.type == REDIRECTION || token.type == APPEND) && token.arg_count)
			printf("Output : %s\n", token.args[0]);
		printf("--------------------------------\n");
		tmp = tmp->next;
	}
}
