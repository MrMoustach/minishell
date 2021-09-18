/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 16:33:29 by zed               #+#    #+#             */
/*   Updated: 2021/09/18 16:44:05 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../headers/minishell.h"

char	**sort_env(char **envp)
{
	int		i;
	char	*tmp;
	int		flag;

	while (1)
	{
		flag = 1;
		i = 0;
		while (envp[i + 1])
		{
			if (ft_strncmp(envp[i], envp[i + 1], ft_strlen(envp[i])) > 0)
			{
				tmp = envp[i + 1];
				envp[i + 1] = envp[i];
				envp[i] = tmp;
				flag = 0;	
			}
			i++;
		}
		if (flag)
			break ;
	}
	return (envp);
}