/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/28 18:12:03 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_minishell(char **envp, char **av, int ac)
{
	char *line;
	t_list *tokens;
	
	while (1)
	{
		line = readline(g_shell.prompt);
		if (!line)
		{
			printf("BYE CRUEL WORLD\n");
			return (1);
		}
		if (!*line)
			continue;
		add_history(line);
		tokens = parser(line);
		print_helper(tokens);
		tokens = expand_tokens(tokens);
		print_helper(tokens);
		reparse_commands(tokens);
		printf("reparsed commands\n");
		print_helper(tokens);
		builtin_execute(tokens);
		free(line);
		refresh_shell();
	}
}


void	intSigHandler(int sig)
{
	printf("\n");
    rl_on_new_line();
    rl_replace_line("", 0);
    rl_redisplay();
}

int	main(int ac, char **av, char **envp)
{
	init_shell(envp, av);
	signal(SIGINT, intSigHandler);
	run_minishell(envp, av, ac);
}