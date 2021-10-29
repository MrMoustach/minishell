/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect_append.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:08:37 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 21:33:34 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	heredoc(t_token redirect)
{
	int		file;
	char	*line;
	char	*tmp;

	file = open ("/tmp/lmao", O_WRONLY | O_CREAT, 0644);
	line = NULL;
	while (1)
	{
		line = readline("heredocs>");
		if (!line)
			break ;
		if (!ft_strncmp(line, redirect.args[0], ft_strlen(line) + 1))
			break ;
		tmp = exp_string(line);
		write (file, tmp, ft_strlen(tmp));
		write (file, "\n", 1);
		free (line);
		free (tmp);
	}
	free(line);
	close (file);
}

int	create_or_open_file(t_token redirect)
{
	int	fd;
	int	flag;

	if (redirect.direction == e_right)
	{
		flag = O_CREAT;
		if (redirect.type == e_append)
			flag = O_CREAT | O_WRONLY | O_APPEND;
		else
			flag = flag | O_WRONLY | O_TRUNC;
		fd = open(redirect.args[0], flag, 0644);
	}
	else
	{
		if (redirect.type == e_redirect)
			fd = open(redirect.args[0], O_RDONLY, 0644);
		if (redirect.type == e_append)
		{
			heredoc(redirect);
			fd = open("/tmp/lmao", O_RDONLY);
		}
	}
	return (fd);
}
