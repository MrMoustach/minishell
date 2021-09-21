/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:18:57 by zed               #+#    #+#             */
/*   Updated: 2021/09/21 15:26:59 by zed              ###   ########.fr       */
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

typedef struct	s_syntax
{
	t_token		current;
	t_token		prev;
	t_token		next;
	int			context;
	int			error;
}				t_syntax;
#endif