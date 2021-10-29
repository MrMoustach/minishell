/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:13:22 by zed               #+#    #+#             */
/*   Updated: 2021/10/29 21:44:34 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include "../libft/libft.h"
# include "types.h"
# include <readline/readline.h>
# include <readline/history.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>
# include <fcntl.h>

char		**sort_env(char **envp);
void		add_token(t_token *token, t_list **tokens);
t_token		*create_token(char *str);
void		tokenizer(t_list *tokens);
t_spliter	spliter(char *line);
char		*ft_chardup(char c, int n);
t_syntax	syntax_analysis(t_list *tokens);
t_list		*parser(char	*line);
void		reparse_commands(t_list	*tokens);
void		free_token(void *t);
void		parser_last_command(t_token **tmp_token,
				t_list **tokens, t_parser *parser, t_list **list);
void		parser_beofre_command(t_parser *parser, t_list **list);
int			parse_switch_arg(t_parser *parser, t_list **list,
				t_token *tmp_token, t_list **tokens);
void		builtin_execute(t_token command);
int			builtin_echo(t_token command);
int			builtin_pwd(t_token command);
int			builtin_env(t_token command);
void		builtin_exit(t_token command);
int			builtin_export(t_token command);
int			builtin_unset(t_token command);
int			builtin_cd(t_token command);
int			is_builtin(t_token command);
char		*ft_getenv(char *name);
char		**dup_env(char **envp);
void		ft_addenv(char *var);
char		**sort_env(char **envp);
void		ft_delenv(char *var);
char		**split_equals(char *str);
int			compare_env(char *name, char *var);
void		ft_modenv(char *name, char *line);
void		split_quotes(t_spliter *spliter, char *line);
int			split_append(t_spliter *spliter, char *line);
int			split_end(t_spliter *spliter, char *line);
t_spliter	*split_extra(t_spliter *spliter, char *line, char delim);
void		free_tab(char **tab);
int			ft_is_number(char *s);
long long	ft_atol(const char *str);
int			table_count(char **table);
char		**add_to_array(char **array, char *str, int count);
char		**add_to_top_array(char **array, char *str, int count);
char		*trim_starting_whitespaces(char *str);
t_list		*expand_tokens(t_list *tokens);
void		expand_command_token(t_token *command);
char		*exp_stripe_quotes(char *str, size_t *length);
int			exp_is_var(char c);
void		expand_command_token(t_token *command);
char		*exp_string(char *str);
size_t		exp_str_size(char *str);
char		*exp_current_var(char *src, size_t end);
int			exp_create_context(char c, int con);
void		exp_str_size_var(char *str, size_t *i, size_t *count);
size_t		exp_str_size(char *str);
void		execute_line(t_list	*tokens);
int			execute_command(t_token command);
t_list		*assign_io(t_list *tokens);
t_queue		init_case_commant(t_queue queue);
t_queue		assignment_logic(t_queue queue);
t_queue		pipe_after_command(t_queue queue);
t_queue		case_append_redirect(t_queue queue);
t_queue		case_pipe(t_queue queue);
t_queue		case_command(t_queue queue);
void		heredoc(t_token redirect);
int			create_or_open_file(t_token redirect);
void		init_shell(char	**envp);
void		refresh_shell(void);
void		clean_shell(t_list *tokens, char *line);
void		int_sig_handler(int sig);
void		quit_sig_handler(int sig);
void		handle_errors(t_token	*token, char	*message);
t_binary	locate_bin(char	*str);
int			execute_binary(t_binary binary, t_token command);
int			bin_exist_in_path(t_binary binary);

extern t_shell	g_shell;
#endif