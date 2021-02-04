/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:15:08 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 10:41:59 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void signal_handler(int sig)
{
	PRINT("%d", sig);
}
int main(int argc, char *argv[], char *envp[])
{
	int	killSig;
	char *line;
	t_list *commands;
	
	killSig = 1;
	chdir("..");
	init_shell(envp);
	signal(SIGINT, signal_handler);
	(void) argc;
	(void) argv;
	while (killSig)
	{
		PRINT("\e[44m%s \e[49m>",state.cwd);
		get_next_line(0, &line);
		if (*line == '\0')
			continue;
		commands = parse(line);
		check_commands(commands);
	}
	system("clear");
	return (0);
}