/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:15:08 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 19:03:53 by iharchi          ###   ########.fr       */
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
	init_shell(envp);
	signal(SIGINT, signal_handler);
	(void) argc;
	(void) argv;
	while (killSig)
	{
		refresh_shell();
		get_next_line(0, &line);
		if (*line == '\0')
			continue;
		commands = parse(line);
		check_commands(commands);
	}
	system("clear");
	return (0);
}