/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 14:11:43 by omimouni          #+#    #+#             */
/*   Updated: 2021/09/26 10:47:31 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void
	exp_str(char *str)
{
	size_t	count;
	size_t	 i;

	count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			// TODO: add helper to know the end of variable
			while (str[i] != ' ' && str[i] != '\0')
				i++;
		}
		else
			count++;
		i++;
	}
	printf("%zu \n", count);
}

void
	expand_command_token(t_token *command)
{
	exp_str(command->str);
	
	printf("\n-----------\n");
	printf("command: %s \n", command->str);
	printf("-----------\n");
}