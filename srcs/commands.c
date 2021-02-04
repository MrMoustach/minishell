/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   commands.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:36:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 16:15:51 by iharchi          ###   ########.fr       */
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
	return (chdir(args[1]));
}

int	debug_test(char **args, int argc)
{
	(void) args;
	(void) argc;
	char *env_args[] = {(char*)0};
	PRINT("%d", execve(args[1], &args[1], env_args));
	return (0);
}

int	command_ls(char **args, int argc)
{
	char	*path;
	DIR		*dir;
	struct	dirent *dp;
	
	
	if (argc < 2)
		path = ft_strdup(".");
	else
		path = args[1];
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
int	command_env(char **args, int argc)
{
	int	i;

	i = 0;
	(void) args;
	(void) argc;
	while (state.envp[i])
	{	
		write (0, state.envp[i], ft_strlen(state.envp[i]));
		write (0, "\n", 1);
		i++;
	}
	return (0);
}

int	debug_exit(char **args, int argc)
{
	(void) argc;
	(void) args;
	exit(0);
	return (0);
}

int	debug_clear(char **args, int argc)
{
	(void) args;
	(void) argc;
	system("clear");
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
	
	i = 1;
	new_line = 1;
	escape_flag = 0;
	while (args[i] && argc > 1)
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
					word = get_next_word(&args[i][j + 1]);
					env = ft_get_env(word);
					j += ft_strlen(word) + 1;
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

int	command_pwd(char **args, int argc)
{
	(void) args;
	(void) argc;
	refresh_shell();
	write (0, state.cwd, ft_strlen(state.cwd));
	write (0, "\n", 1);
	return (0);
}

int	check_commands(t_list *commands)
{
	t_list	*tmp;
	t_command command;
	int	i;
	t_list	*tmp_built;
	t_builtin	builtin;

	tmp = commands;
	while (tmp)
		{
			command = *(t_command *)tmp->content;
			PRINT("Command : %s\n", command.command);
			i = 1;
			if (command.argc > 1)
			{
				PRINT("%s", "args :");
				while (command.args[i])
				{
					PRINT(" %s, ", command.args[i++]);
				}
			}
			if (command.argc > 1)
			{
				PRINT("%s","\n");
			}
			tmp = tmp->next;
			tmp_built = state.builtins;
			while (tmp_built)
			{
				builtin = *(t_builtin *)(tmp_built->content);
				if (!ft_strncmp(builtin.command, command.command, ft_strlen(builtin.command)))
				{	
					builtin.opt(command.args, command.argc);
					break ;
				}
				tmp_built = tmp_built->next;
			}
			if (tmp_built == NULL)
			{	
				write (0, "Command : ", 8);
				write (0, command.command, ft_strlen(command.command));
				write (0, " not found\n", 15);
			}
		}
		return (0);
}