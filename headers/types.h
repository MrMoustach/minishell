/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:18:57 by zed               #+#    #+#             */
/*   Updated: 2021/09/18 16:46:22 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

//DOCS :	COMMADN	  arg  <>			>><<    |     ;     &   everthing else
enum e_type {COMMAND, ARG, REDIRECTION, APPEND, PIPE, END, AND, RANDOM};

typedef struct	s_token
{
	enum e_type type;
	char		*str;
	char		direction;
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