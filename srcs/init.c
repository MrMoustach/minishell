/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:30:38 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 17:03:19 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(char *envp[])
{
	char *cwd;
	
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	state.cwd = cwd;
	state.envp = envp;
	state.builtins = NULL;
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("cd", command_cd)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("echo", command_echo)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("pwd", command_pwd)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("ls", command_ls)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("env", command_env)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("exit", debug_exit)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("clear", debug_clear)));
	ft_lstadd_back(&(state.builtins), ft_lstnew(create_builtin("test", debug_test)));
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
	free(state.cwd);
	state.cwd = NULL;
	state.cwd = getcwd(state.cwd, 0);
	PRINT("\e[44m%s \e[49m>",state.cwd);
}