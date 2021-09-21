/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/21 16:06:37 by zed              ###   ########.fr       */
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


		// if (!syntax.prev.empty)
		// 	printf("prev token : %s | ", syntax.prev.str);
		// printf("current token : %s | ", syntax.current.str);
		// if (!syntax.next.empty)
		// 	printf("next token : %s", syntax.next.str);
		// printf("\n");
		syntax.prev = syntax.current;
		syntax.current = syntax.next;
		tmp = tmp->next;
	}
	return (syntax);
}

int	main(int ac, char **av, char **envp)
{
	t_spliter split;
	t_list	*tmp;
	t_token	token;
	char	*line;
	t_syntax	syntax;
	envp = sort_env(envp);
	// (omar) TODO  : Provide the line, and work on history / readline stuff
	// (issam) TODO : parse line into idividual commands, expand what can be expanded, and escape stuff return data as a command struct
	while (1)
	{
		line = readline(FT_PROMPT);
		if (!line)
		{
			printf("BYE\n");
			return (1);
		}
		if (!*line)
			continue;
		add_history(line);
		split = spliter(line);
		tokenizer(split.tokens);
		tmp = split.tokens;
		syntax = syntax_analysis(split.tokens);
		if (syntax.error)
		{
			printf("syntax error m8 code : %d near %s\n", syntax.error, syntax.err_token.str);
			continue;
		}
		while (tmp)
		{
			token = *((t_token *)tmp->content);
			printf("TOKEN : %s\n", token.str);
			printf("TYPE : ");
			printf("%s\n", types[(int)token.type]);
			printf("--------------------------------\n");
			tmp = tmp->next;
		}
		free(line);
	}
}