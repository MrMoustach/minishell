/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/24 19:03:35 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/25 16:44:40 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// (issam) TODO : fix this segfault
void	builtin_unset(t_token command)
{
	int		i;
	char	*tmp;

	i = 0;
	if (command.arg_count)
	{
		while (command.args[i])
		{
			tmp = ft_getenv(command.args[i]);
			if (tmp != NULL)
			{
				if (ft_strchr(command.args[i], '=') == NULL)
					ft_delenv(command.args[i]);
				free (tmp);
			}
			i++;
		}
	}
	else
		printf("unset: not enough arguments\n");
}