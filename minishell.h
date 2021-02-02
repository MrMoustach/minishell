/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/02 11:12:14 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/02 18:36:14 by iharchi          ###   ########.fr       */
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

char  **parse_line(char *line);
t_list	*parse(char *line);

typedef struct	s_command
{
	char		*command;
	char		**args;
	int			argc;
	int			token;
}				 t_command;
typedef struct	s_state
{
	char		*cwd;
	t_list		*task;
	t_list		*vars;
	char		*last_output;
}				t_state;

t_state state;
#endif