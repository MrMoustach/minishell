/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:11:49 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 12:01:02 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int		get_nbr_commands(char *line)
{
	int	i;
	int	context;
	int	j;

	i = 0;
	j = 0;
	context = 0;
	while (line[i])
	{
		if (context == 0)
		{
			if (line[i] == '"')
				context = 1;
			if (line[i] == '\'')
				context = 2;
			if (line[i] == ';')
				j++;
		}
		else if ((context == 1 && line[i] == '"') || (context == 2 && line[i] == '\''))
				context = 0;
		i++;
	}
	return (j + 1);
}


char	**parse_line(char *line)
{
	char	**commands;
	int		context;
	int		i;
	int		j;
	int		last;
	
	i = 0;
	context = 0;
	j = 0;
	last = 0;
	commands = malloc((get_nbr_commands(line) + 1) * sizeof(char *));
	while (line[i])
	{
		if (context == 0)
		{
			if (line[i] == '"')
				context = 1;
			if (line[i] == '\'')
				context = 2;
			if (line[i] == ';')
			{
				commands[j] = ft_substr(line , last, i - last);
				last = i + 1;
				j++;
			}
		}
		else if ((context == 1 && line[i] == '"') || (context == 2 && line[i] == '\''))
				context = 0;
		i++;
	}
	if (last - 1 < i)
		commands[j++] = ft_substr(line, last, i); 
	commands[j] = 0;
	return (commands);
}

int get_tab_size(char **tab)
{
	int i;

	i = 0;
	while (tab[i])
		i++;
	return (i);
}

t_command	parse_command(char *command)
{
	t_command ret;
	char **tab;
	int	i;
	
	//TODO : change this to ignore spaces in quotes
	// tab = ft_split(command, ' ');
	tab = ft_split_args(command, ' ');
	ret.command = tab[0];
	ret.argc = get_tab_size(tab);
	if (ret.argc > 1)
	{
		ret.args = malloc(ret.argc * sizeof(char *));
		i = 1;
		while (tab[i])
		{
			ret.args[i - 1] = tab[i];
			i++;
		}
		ret.token = -1;
	}
	return (ret);
}

t_list	*parse(char *line)
{
	char **commands;
	t_list	*list_of_commands;
	t_command	*command;
	int	i;
	
	commands = parse_line(line);
	i = 0;
	list_of_commands = NULL;
	while (commands[i])
	{
		command = malloc(sizeof(t_command));
		*command = parse_command(commands[i++]);
		ft_lstadd_back(&list_of_commands, ft_lstnew(command));
	}
	return (list_of_commands);
}
