/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   types.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:18:57 by zed               #+#    #+#             */
/*   Updated: 2021/09/17 17:38:22 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TYPES_H
# define TYPES_H

enum e_type {COMMAND, ARG, REDIRECTION, PIPE, END};

typedef struct	s_token
{
	enum e_type type;
	char		*str;
	char		redirect;
}				t_token;

typedef struct	s_spliter
{
	int		i;
	int		in_quotes;
	char	quotes;
	char	*last_word;
	int		word_start;
}				t_spliter;
#endif