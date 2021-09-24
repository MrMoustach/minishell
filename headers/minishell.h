/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 14:13:22 by zed               #+#    #+#             */
/*   Updated: 2021/09/23 17:48:56 by zed              ###   ########.fr       */
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

char	**sort_env(char **envp);
void	add_token(t_token *token, t_list **tokens);
t_token	*create_token(char *str);
void	tokenizer(t_list *tokens);
t_spliter spliter (char *line);
char	*ft_chardup(char c, int n);
t_syntax	syntax_analysis(t_list *tokens);
void	parser(char	*line);
#endif