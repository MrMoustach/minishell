/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/26 17:55:05 by zed               #+#    #+#             */
/*   Updated: 2021/09/27 13:16:35 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"


// (issam) TODO : fix this segfault
void	builtin_unset(t_token command)
{
	int	i;

	i = 0;
	if (command.arg_count)
	{
		while (command.args[i])
		{
			if (ft_strchr(command.args[i], '=') == NULL)
				ft_delenv(command.args[i]);
			i++;
		}
	}
}