/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:35:17 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/17 10:05:27 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	builtin_echo(t_token command)
{
	int	new_line;
	int	i;

	new_line = 1;
	if (command.arg_count)
	{
		i = 0;
		if (!ft_strncmp(command.args[0], "-n", 3))
		{
			i++;	
			new_line = 0;
		}
		while (command.args[i])
			printf("%s", command.args[i++]);
	}
	if (new_line)
		printf("\n");
}