/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:30:38 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/17 17:17:32 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(char *envp[])
{
	char	*cwd;
	char	*tmp;
	
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	state.cwd = cwd;
	state.envp = dup_tab(envp);
	state.builtins = NULL;
	state.succes = 0;
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("cd", command_cd)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("echo", command_echo)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("pwd", command_pwd)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("env", command_env)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("exit", debug_exit)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("export", command_export)));
	tmp = ft_get_env("_");
	ft_set_env("SHELL", tmp);
	free(tmp);
}
t_builtin	*create_builtin(char *s, int (*opt)(char **args, int argc))
{
	t_builtin	*command;

	command = malloc(sizeof(t_builtin));
	command->command = s;
	command->opt = opt;
	return (command);
}
void refresh_shell()
{
	char *user;
	
	free(state.cwd);
	state.cwd = NULL;
	state.cwd = getcwd(state.cwd, 0);
	user = ft_get_env("USER");
	state.succes = 0;
	write (0, "\n", 1);
	write (0, user, ft_strlen(user));
	free(user);
	write (0, "\e[34m@", 6);
	write (0, "\e[1m\e[32m", 9);
	write (0, state.cwd, ft_strlen(state.cwd));
	write (0, "\e[39m\e[5m>\e[0m ", ft_strlen("\e[39m\e[5m>\e[0m "));
}