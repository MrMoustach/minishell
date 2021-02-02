/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:15:08 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/02 18:50:40 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int main()
{
	int	killSig;
	char *line;
	t_list *commands;
	int		i;
	killSig = 1;

	while (killSig)
	{
		write(0,">",1);
		get_next_line(0, &line);
		commands = parse(line);
		while (commands)
		{
			PRINT("Command : %s\n", ((t_command *)commands->content)->command);
			i = 0;
			while (i < ((t_command *)commands->content)->argc - 1)
			{
				PRINT("args : %s\n", ((t_command *)commands->content)->args[i++]);
			}
			commands = commands->next;
		}
	}
	return (0);
}