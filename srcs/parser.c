/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:11:49 by iharchi           #+#    #+#             */
/*   Updated: 2021/03/10 12:03:46 by iharchi          ###   ########.fr       */
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

int			get_type_command(char *command)
{
	char *stripped;

	stripped = ft_strtrim(command, "'\"");
	if (ft_strncmp(stripped, EXPORT, ft_strlen(EXPORT)) || ft_strncmp(stripped, SET, ft_strlen(SET)))
	{
		free(stripped);
		return (COMMAND_SETTER);
	}
	free(stripped);
	return (COMMAND_NORMAL);
}

// FIXME:  dyfunctional
/*
** this function parses the invidual command and strip its args from quotes, it 
** it has a lot of bugs 
** Needs to be changed
*/
t_command	parse_command(char *command)
{
	t_command ret;
	char		*tmp;
	// TODO : 	Replace tilde with the home if its not procesded with a character
	//			and does have something other than / or whitespace after it
	command = replace_envvars(command);
	ret.args = ft_split_args(command, ' ');
	ret.type = get_type_command(ret.args[0]);
	// FIXME: FT_STRTRIM doesnt work when env="stuff"
	if (ret.type != COMMAND_SETTER)
		ret.args = strip_quotes(ret.args);
	else
	{
		tmp = ft_strtrim(ret.args[0], "'\"");
		free(ret.args[0]);
		ret.args[0] = tmp;
	}
	ret.command = ret.args[0];
	ret.argc = get_tab_size(ret.args);
	free(command);
	return (ret);
}

char	**strip_quotes(char **tab)
{
	int	i;
	char **ret;

	i = 0;
	ret = malloc((get_tab_size(tab) + 1) * sizeof(char *));
	while (tab[i])
	{
		ret[i] = ft_strtrim(tab[i], "\"'");
		i++;
	}
	ret[i] = NULL;
	free_tab(tab);
	return (ret);
}

t_list	*parse(char *line)
{
	char **commands;
	t_list	*list_of_commands;
	t_command	*command;
	int	i;
	
	commands = parse_line(line);
	free(line);
	i = 0;
	list_of_commands = NULL;
	while (commands[i])
	{
		command = malloc(sizeof(t_command));
		*command = parse_command(commands[i++]);
		ft_lstadd_back(&list_of_commands, ft_lstnew(command));
	}
	free(commands);
	return (list_of_commands);
}
