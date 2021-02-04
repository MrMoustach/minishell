/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:36:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 12:23:24 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	command_cd(char **args, int argc)
{
	char	*path;
	int		ret;
	if (argc < 2)
	{
		path = ft_get_env("HOME");
		ret = chdir(path);
		free(path);
		return (ret);
	}
	if (argc > 2)
		return (-2);
	return (chdir(args[0]));
}

int	command_ls(char **args, int argc)
{
	char	*path;
	DIR		*dir;
	struct	dirent *dp;
	
	
	if (argc < 2)
		path = ft_strdup(".");
	else
		path = args[0];
	if (argc > 2)
	{
		//free
		return (-2);
	}
	if ((dir = opendir(path)))
	{
		while ((dp = readdir(dir)))
		{
			if (dp->d_type == 4)
			{
				PRINT(" \e[32m%s\e[39m \n", dp->d_name);
			}
			else
			{
				PRINT(" %s \n", dp->d_name);
			}
			
		}
	}
	else
		return (-3);
	return (0);
		
}
int	command_env()
{
	int	i;

	i = 0;
	while (state.envp[i])
	{	
		write (0, state.envp[i], ft_strlen(state.envp[i]));
		write (0, "\n", 1);
		i++;
	}
	return (0);
}

int	command_echo(char **args, int argc)
{
	int	i;
	int	new_line;
	int	j;
	int	escape_flag;
	char *env;
	char *word;
	
	i = 0;
	new_line = 1;
	escape_flag = 0;
	(void) argc;
	while (args[i])
	{
		if (!ft_strncmp(args[i], "-n", 3))
			new_line = 0;
		else
		{
			j = 0;
			while (args[i][j])
			{
				if (args[i][j] == '$')
				{
					word = get_next_word(&args[i][i + 1]);
					env = ft_get_env(word);
					j += ft_strlen(word + 1);
					free(word);
					write (0, env, ft_strlen(env));
					free(env);
				}
				if (args[i][j] == '"' && escape_flag == 0)
					escape_flag = 1;
				else if ((args[i][j] == '"' && escape_flag == 1) || (args[i][j] == '\'' && escape_flag == 2))
					escape_flag = 0;
				else if(args[i][j] == '\'' && escape_flag == 0)
					escape_flag = 2;
				else
					write (0, &args[i][j], 1);
				j++;
			}
			write (0, " ", 1);
		}
		i++;
	}
	if (new_line)
		write (0, "\n", 1);
	return (0);
}

int	check_commands(t_list *commands)
{
	t_list	*tmp;
	t_command command;
	int	i;

	tmp = commands;
	while (tmp)
		{
			command = *(t_command *)tmp->content;
			PRINT("Command : %s\n", command.command);
			i = 0;
			if (command.argc > 1)
			{
				PRINT("%s", "args :");
			}
			while (i < command.argc - 1)
			{
				PRINT(" %s, ", command.args[i++]);
			}
			if (command.argc > 1)
			{
				PRINT("%s","\n");
			}
			tmp = tmp->next;
			if (!ft_strncmp(command.command, "cd", 3))
			{
				int error_code = command_cd(command.args, command.argc);
				if (error_code == 0)
				{	
					refresh_shell();
				}
				else
				{
					PRINT("Error_code : %d\n",error_code);
				}
			}
			else if (!ft_strncmp(command.command, "ls", 3))
			{
				int error_code = command_ls(command.args, command.argc);
				if (error_code != 0)
				{
					PRINT("Error_code: %d", error_code);
				}
			}
			else if (!ft_strncmp(command.command, "clear", 5))
			{
				system("clear");
			}
			else if (!ft_strncmp(command.command, "env", 4))
			{
				command_env();
			}
			else if (!ft_strncmp(command.command, "echo", 5))
			{
				command_echo(command.args, command.argc);
			}
			else if (!ft_strncmp(command.command, "exit", 5))
			{
				exit(0);
			}
			else{
				PRINT("%s", "Command not found\n");
			}
		}
		return (0);
}