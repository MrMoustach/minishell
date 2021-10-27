/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:03:35 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/27 14:40:52 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// BUG: segfaults
void	find_and_delete(char *env)
{
	char	*tmp;

	tmp = ft_getenv(env);
	if (tmp != NULL)
	{
		ft_delenv(env);
		free (tmp);
	}
}

int	builtin_unset(t_token command)
{
	int		i;
	int		ret;

	i = 0;
	ret = 1;
	if (command.arg_count)
	{
		while (command.args[i])
		{
			if (ft_strchr(command.args[i], '='))
				printf("unset: %s invalid parameter name", command.args[i]);
			else
			{
				ret = 0;
				find_and_delete(command.args[i]);
			}
			i++;
		}
	}
	else
		printf("unset: not enough arguments\n");
	return (ret);
}
