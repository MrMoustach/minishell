/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:17:14 by zed               #+#    #+#             */
/*   Updated: 2021/09/25 11:53:04 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	run_minishell(void)
{
	char *line;
	t_list *tokens;
	
	// (omar) TODO  : Provide the line, and work on history / readline stuff
	// (issam) TODO : parse line into idividual commands, expand what can be expanded, and escape stuff return data as a command struct
	while (1)
	{
		line = readline(FT_PROMPT);
		if (!line)
		{
			printf("BYE CRUEL WORLD\n");
			return (1);
		}
		if (!*line)
			continue;
		add_history(line);
		tokens = parser(line);
		builtin_execute(tokens);
		free(line);
	}
}

void init_shell(char	**envp)
{
	g_shell.run = 1;
	g_shell.envp = dup_env(envp);
	g_shell.envp = sort_env(g_shell.envp);
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
	init_shell(envp);
	signal(SIGINT, intSigHandler);
	run_minishell();
}