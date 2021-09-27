/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:13:22 by zed               #+#    #+#             */
/*   Updated: 2021/09/27 18:38:55 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "types.h"
# include "dev.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>

char	**sort_env(char **envp);
void	add_token(t_token *token, t_list **tokens);
t_token	*create_token(char *str);
void	tokenizer(t_list *tokens);
t_spliter spliter (char *line);
char	*ft_chardup(char c, int n);
t_syntax	syntax_analysis(t_list *tokens);
t_list	*parser(char	*line);


/**
** Builtins
**/
void	builtin_execute(t_list *tokens);
void	builtin_echo(t_token command);
void	builtin_pwd(t_token command);
void	builtin_env(t_token command);
void	builtin_exit(t_token command);
void	builtin_export(t_token command);
void	builtin_unset(t_token command);
void	builtin_cd(t_token command);

char	*ft_getenv(char *name);

/**
** env
**/
char	**dup_env(char **envp);
void	ft_addenv(char *var);
char	**sort_env(char **envp);
void	ft_delenv(char *var);
char	**split_equals(char *str);
int		compare_env(char *name, char *var);
void	ft_modenv(char *name, char *line);
/**
** Utility
**/
void free_tab(char **tab);
int	ft_is_number(char *s);
long long	ft_atol(const char *str);
int		table_count(char **table);


/**
 * Expansion
 */
t_list	*expand_tokens(t_list *tokens);
void	expand_command_token(t_token *command);

/***
 * shell
*/
void init_shell(char	**envp, char **av);
void refresh_shell();

extern t_shell	g_shell;
#endif