/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/10/17 10:08:53 by omimouni         ###   ########.fr       */
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
		line = trim_starting_whitespaces(line);
		if (!*line)
			continue;
		add_history(line);
		tokens = parser(line);
		if (g_shell.error)
		{
			refresh_shell();
			continue ;
		}
		if (g_shell.debug_mode == 2)
			print_helper(tokens);
		tokens = expand_tokens(tokens);
		if (g_shell.debug_mode == 1)
		{
			print_helper(tokens);
			printf("reparsed commands\n");
		}
		reparse_commands(tokens);
		if (g_shell.debug_mode == 2)
			print_helper(tokens);
		tokens = assign_io(tokens);
		if (g_shell.debug_mode == 4)
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
	g_shell.last_status = 0;
	init_shell(envp, av, ac);
	signal(SIGINT, intSigHandler);
	run_minishell(envp, av, ac);
}