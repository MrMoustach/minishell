/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:04:45 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 20:52:39 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_shell	g_shell;

int	catch_errors(t_list *tokens, char *line)
{
	if (g_shell.error)
	{
		clean_shell(tokens, line);
		return (1);
	}
	return (0);
}

t_list	*use_tokens(t_list	*tokens)
{
	tokens = expand_tokens(tokens);
	reparse_commands(tokens);
	tokens = assign_io(tokens);
	return (tokens);
}

char	*get_line(void)
{
	char	*line;

	line = readline(g_shell.prompt);
	if (!line)
	{
		printf("BYE CRUEL WORLD\n");
		exit (g_shell.last_status);
	}
	line = trim_starting_whitespaces(line);
	return (line);
}

int	run_minishell(void)
{
	char	*line;
	t_list	*tokens;

	while (1)
	{
		line = get_line();
		if (!*line)
		{
			free (line);
			continue ;
		}
		add_history(line);
		tokens = parser(line);
		if (catch_errors(tokens, line))
			continue ;
		tokens = use_tokens(tokens);
		if (catch_errors(tokens, line))
			continue ;
		execute_line(tokens);
		clean_shell(tokens, line);
	}
}

int	main(int ac, char **av, char **envp)
{
	(void)ac;
	(void)av;
	g_shell.last_status = 0;
	g_shell.pid = 1;
	init_shell(envp);
	signal(SIGINT, int_sig_handler);
	signal(SIGQUIT, quit_sig_handler);
	run_minishell();
}
