/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/29 15:29:53 by iharchi          ###   ########.fr       */
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
		// (issam) TODO : trim spaces from the line
		line = trim_starting_whitespaces(line);
		add_history(line);
		tokens = parser(line);
		if (g_shell.debug_mode == 2)
			print_helper(tokens);
		// FIXME:
		// (omar) TODO: $? needs to be expandable to g_shell.exit_code
		tokens = expand_tokens(tokens);
		if (g_shell.debug_mode == 2)
		{
			print_helper(tokens);
			printf("reparsed commands\n");
		}
		reparse_commands(tokens);
		if (g_shell.debug_mode == 1)
			print_helper(tokens);
		execute_line(tokens);
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
	init_shell(envp, av, ac);
	signal(SIGINT, intSigHandler);
	run_minishell(envp, av, ac);
}