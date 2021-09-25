/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dev.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/18 22:45:58 by zed               #+#    #+#             */
/*   Updated: 2021/09/25 14:33:25 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
char *types[] = {"COMMAND", "ARG", "REDIRECTION", "APPEND", "PIPE", "END", "AND", "FILE", "RANDOM"};

void	print_helper(t_list *tokens)
{
	t_list	*tmp;
	t_token	token;
	int		i;
	
	tmp = tokens;
	printf("--------------------------------\n");
	while (tmp)
	{
		token = *((t_token *)tmp->content);
		printf("TOKEN : %s\n", token.str);
		printf("TYPE : ");
		printf("%s\n", types[(int)token.type]);
		if (token.arg_count > 0 && token.type == COMMAND)
		{
			i = 0;
			printf("%d ARGS : ", token.arg_count);
			while (i < token.arg_count)
				printf("%s ", token.args[i++]);
			printf("\n");
		}
		if (token.type == REDIRECTION || token.type == APPEND)
		{
			printf("DIRECTION : ");
			if (token.direction == RIGHT)
				printf("RIGHT\n");
			else
				printf("LEFT\n");
			if (token.arg_count)
				printf("FILE : %s\n", token.args[0]);
		}
		printf("--------------------------------\n");
		tmp = tmp->next;
	}
}

void	debug_leaks(void)
{
	system("leaks minishell");
}