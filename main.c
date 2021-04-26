/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:15:08 by iharchi           #+#    #+#             */
/*   Updated: 2021/03/10 12:36:41 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void signal_handler(int sig)
{
	(void) sig;
	write (0, "\n", 1);
	refresh_shell();
}
int main(int argc, char *argv[], char *envp[])
{
	int	killSig;
	char *line;
	t_list *commands;
	
	killSig = 1;
	state.argv = argv;
	state.argc = argc;
	init_shell(envp);
	signal(SIGINT, signal_handler);
	int fd = open("command", O_RDONLY);
	while (killSig)
	{
		refresh_shell();
		// char *buffer = malloc(2048);
		// tgetent(buffer, getenv("TERM")); //TERM = xterm-256color
		// char *key_up = tgetstr("ku", &buffer); // gives me \EOA
		get_next_line(0, &line);
		if (*line == '\0')
			continue;
		commands = parse(line);
		check_commands(commands);
		ft_lstclear(&commands, free_command);
		free(commands);
	}
	close (fd);
	system("clear");
	return (0);
}