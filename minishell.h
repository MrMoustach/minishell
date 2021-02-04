/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:12:14 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 16:37:22 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include "libft/libft.h"
# include "gnl/get_next_line.h"
# include "dev.h"
# include <dirent.h>
# include <signal.h>

typedef struct	s_command
{
	char		*command;
	char		**args;
	int			argc;
	int			token;
}				 t_command;

typedef	struct	s_builtin
{
	char		*command;
	int			(*opt)(char **args, int argc);
}				t_builtin;

typedef struct	s_state
{
	char		*cwd;
	t_list		*commands;
	char		**envp;
	t_list		*vars;
	char		*last_output;
	t_list		*builtins;
}				t_state;

char  **parse_line(char *line);
t_list	*parse(char *line);
void	init_shell(char *envp[]);
int	command_cd(char **args, int argc);
int	command_ls(char **args, int argc);
void refresh_shell();
int	check_commands(t_list *commands);
void    free_tab(char **tab);
char *ft_get_env(char *env);
int	command_env(char **args, int argc);
int	command_echo(char **args, int argc);
char			**ft_split_args(char const *str, char c);
char *get_next_word(char *s);
char	**strip_quotes(char **tab);
int	command_pwd(char **args, int argc);
t_builtin	*create_builtin(char *s, int (*opt)(char **args, int argc));
int	debug_exit(char **args, int argc);
int	debug_clear(char **args, int argc);
int	debug_test(char **args, int argc);
int main(int argc, char *argv[], char *envp[]);

t_state state;
#endif