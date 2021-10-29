/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 11:36:47 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 15:38:41 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	builtin_pwd(t_token command)
{
	char	*str;

	if (command.arg_count)
	{
		g_shell.error = 8;
		handle_errors(NULL, NULL);
		return (1);
	}
	str = ft_getenv("PWD");
	if (str)
	{
		printf("%s\n", str);
		free(str);
	}
	return (0);
}
