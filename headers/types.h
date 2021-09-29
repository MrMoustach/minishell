/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:18:57 by zed               #+#    #+#             */
/*   Updated: 2021/09/29 13:42:50 by iharchi          ###   ########.fr       */
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
	char		debug_mode;
}				t_shell;

#endif