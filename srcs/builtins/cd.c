/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:03:13 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/24 19:03:14 by iharchi          ###   ########.fr       */
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