/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/20 09:35:17 by omimouni          #+#    #+#             */
/*   Updated: 2021/10/28 09:36:00 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	is_n_flag(char *s)
{
	int	i;

	if (s[0] == '-')
	{
		i = 1;
		while (s[i])
		{
			if (s[i] != 'n')
				return (0) ;
			i++;
		}
		return (1);
	}
	return (0);
}

int	builtin_echo(t_token command)
{
	int	new_line;
	int	i;

	new_line = 1;
	i = 0;
	while (1)
	{
		if (is_n_flag(command.args[i]))
		{
			new_line = 0;
			i++ ;
			continue ;
		}
		else
			break ;
		i++;
	}
	while (i < command.arg_count)
	{
		printf("%s", command.args[i++]);
		if (i != command.arg_count)
		printf(" ");
	}

	if (new_line)
		printf("\n");
	return (0);
}
