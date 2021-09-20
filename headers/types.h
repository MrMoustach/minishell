/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:18:57 by zed               #+#    #+#             */
/*   Updated: 2021/09/20 09:26:37 by omimouni         ###   ########.fr       */
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
#endif