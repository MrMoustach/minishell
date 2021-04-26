/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:12:14 by iharchi           #+#    #+#             */
/*   Updated: 2021/03/10 12:36:35 by iharchi          ###   ########.fr       */
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
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>

/*
*	Macros
*/
# define COMMAND_SETTER 911
# define COMMAND_NORMAL 112
# define EXPORT "export"
# define SET "set"
/*
*	Structs
*/
typedef struct	s_command
{
	char		*command;
	char		**args;
	int			argc;
	int			token;
	int			type;
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
	char		**argv;
	int			argc;
	int			succes;
}				t_state;

/*
*	Built-ins
*/

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
void    free_command(void *com);
char	*replace_envvars(char *var);
int	command_export(char **args, int argc);
void	ft_set_env(char	*env, char *line);
void	ft_create_env(char *env, char *line);
int		ft_tablen(char **tab);
char    **dup_tab(char **src);

t_state state;
#endif