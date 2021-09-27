/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/27 16:45:20 by zed               #+#    #+#             */
/*   Updated: 2021/09/27 17:41:18 by zed              ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_cd(t_token command)
{
	char	*path;


	if (command.arg_count)
		path = ft_strdup(command.args[0]);
	else
		path = ft_getenv("HOME");
	if (chdir(path))
		printf ("Mate the dir %s is no more\n", path);
	free (path);
}