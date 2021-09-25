/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:13:22 by zed               #+#    #+#             */
/*   Updated: 2021/09/25 14:29:15 by iharchi          ###   ########.fr       */
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

// Testing expanstion
t_list	*expand_tokens(t_list *tokens);

char	*ft_getenv(char *name);

/**
** env
**/
char	**dup_env(char **envp);

/**
** Utility
**/
void free_tab(char **tab);
int	ft_is_number(char *s);
long long	ft_atol(const char *str);
int		table_count(char **table);

t_shell	g_shell;
#endif