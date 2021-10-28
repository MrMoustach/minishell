/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:18:57 by zed               #+#    #+#             */
/*   Updated: 2021/10/28 15:25:23 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

# define FT_PROMPT "minishell> "

//DOCS :	COMMADN	  arg  <>			>><<    |     ;     &   files everthing else
enum e_type	{COMMAND, ARG, REDIRECTION, APPEND, PIPE, END, AND, FILES, RANDOM};
enum e_dir	{LEFT, RIGHT};
typedef struct	s_token
{
	enum e_type type;
	enum e_dir	direction;
	char		*str;
	int			empty;
	int			arg_count;
	char		**args;
	int			fds[2];
	char		in_pipe;
	char		redirects;
	char		to_close;
}				t_token;

typedef struct	s_spliter
{
	int		i;
	int		in_quotes;
	char	quotes;
	char	*last_word;
	int		word_start;
	t_list	*tokens;
}				t_spliter;

typedef struct	s_var
{
	char	*name;
	char	*line;
}				t_var;

typedef struct	s_syntax
{
	t_token		current;
	t_token		prev;
	t_token		next;
	t_token		err_token;
	int			error;
}				t_syntax;

typedef struct	s_queue
{
	t_token		*current;
	t_token		*prev;
	t_token		*next;
	t_token		*last_command;
	int			p[2];
}				t_queue;

typedef	struct	s_parser
{
	t_token		*last_command;
	t_token		*last_redirect;
	t_token		*current;
	int			context;
}				t_parser;

typedef struct	s_shell
{
	int			run;
	char		**envp;
	char		*prompt;
	char		*name;
	char		command_status;
	int			exit_code;
	char		debug_mode;
	char		error;
	int			last_status;
	int			pid;
}				t_shell;

typedef struct	s_binary
{
	char		*name;
	char		*path;
	char		exist;
}				t_binary;

#endif