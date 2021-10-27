/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:04:45 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/27 16:26:57 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

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
			exit (g_shell.last_status);
		}
		line = trim_starting_whitespaces(line);
		if (!*line)
		{
			free (line);	
			continue;
		}
		add_history(line);
		tokens = parser(line);
		if (g_shell.error)
		{
			ft_lstclear(&tokens, free_token);
			free(line);
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
		if (g_shell.error)
		{
			printf("error: %d\n", g_shell.error);
			ft_lstclear(&tokens, free_token);
			free(line);
			refresh_shell();
			continue ;
		}
		if (g_shell.debug_mode == 4)
			print_helper(tokens);
		execute_line(tokens);
		ft_lstclear(&tokens, free_token);
		free(line);
		refresh_shell();
	}
}


void	intSigHandler(int sig)
{
	if (g_shell.pid == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_shell.last_status = 1;
	}
}
void	quitSigHandler(int sig)
{
	if (g_shell.pid == 1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
// TODO: needs error handling properly
int	main(int ac, char **av, char **envp)
{
	g_shell.last_status = 0;
	g_shell.pid = 1;
	init_shell(envp, av, ac);
	signal(SIGINT, intSigHandler);
	signal(SIGQUIT, quitSigHandler);
	run_minishell(envp, av, ac);
}