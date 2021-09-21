/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/21 16:32:02 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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