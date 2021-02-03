/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:15:08 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/03 18:56:10 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
void signal_handler(int sig)
{
	PRINT("%d", sig);
}
int main()
{
	int	killSig;
	char *line;
	t_list *commands;
	t_command command;
	int		i;
	
	killSig = 1;
	chdir("..");
	init_shell();
	signal(SIGINT, signal_handler);
	while (killSig)
	{
		PRINT("\e[44m%s \e[49m>",state.cwd);
		get_next_line(0, &line);
		commands = parse(line);
		while (commands)
		{
			command = *(t_command *)commands->content;
			PRINT("Command : %s\n", command.command);
			i = 0;
			if (command.argc > 1)
			{
				PRINT("%s", "args :");
			}
			while (i < command.argc - 1)
			{
				PRINT(" %s ", command.args[i++]);
			}
			if (command.argc > 1)
			{
				PRINT("%s","\n");
			}
			commands = commands->next;
			if (!ft_strncmp(command.command, "cd", 2))
			{
				int error_code = command_cd(command.args, command.argc);
				if (error_code == 0)
				{	
					free(state.cwd);
					state.cwd = NULL;
					state.cwd = getcwd(state.cwd, 0);
				}
				else
				{
					PRINT("Error_code : %d\n",error_code);
				}
			}
			else if (!ft_strncmp(command.command, "ls", 2))
			{
				int error_code = command_ls(command.args, command.argc);
				if (error_code != 0)
				{
					PRINT("Error_code: %d", error_code);
				}
			}
			else if (!ft_strncmp(command.command, "clear", 4))
			{
				system("clear");
			}
			else if (!ft_strncmp(command.command, "exit", 4))
			{
				exit(0);
			}
		}
	}
	return (0);
}