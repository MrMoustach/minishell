/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:03:35 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/27 16:26:44 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
				ft_delenv(command.args[i]);
			}
			i++;
		}
	}
	else
		printf("unset: not enough arguments\n");
	return (ret);
}
