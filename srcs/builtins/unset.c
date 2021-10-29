/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:03:35 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 17:02:50 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	unset_arg(char	*env, int ret)
{
	char	*tmp;

	tmp = ft_getenv(env);
	if (ft_strchr(env, '='))
	{
		g_shell.error = 9;
		handle_errors(NULL, env);
		ret = 1;
	}
	else if (tmp != NULL)
		ft_delenv(env);
	free (tmp);
	return (ret);
}

int	builtin_unset(t_token command)
{
	int		i;
	char	*tmp;
	int		ret;

	i = 0;
	ret = 0;
	if (command.arg_count)
	{
		while (command.args[i])
		{
			ret = unset_arg(command.args[i], ret);
			i++;
		}
	}
	else
	{
		ret = 1;
		g_shell.error = 10;
		handle_errors(NULL, "unset: not enough arguments\n");
	}
	return (ret);
}
