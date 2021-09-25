/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 11:38:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/25 11:56:05 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name, char **envp)
{
	char 	*tmp;
	int		i;
	char	**sp;

	i = 0;
	while (envp[i])
	{
		sp = ft_split(envp[i], '=');
		if (!ft_strncmp(sp[0], name, ft_strlen(sp[0])))
			return (ft_strdup(sp[1]));
		// TODO: Free split junk
		i++;
	}
	return (NULL);
}

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

int		table_count(char **table)
{
	int	i;

	i = 0;
	while (table[i])
		i++;
	return (i);
}

char	**dup_env(char **envp)
{
	char	**table;
	int		count;

	count = table_count(envp);
	table = malloc(sizeof(char *) * (count + 1));
	table[count] = NULL;
	while (count--)
		table[count] = ft_strdup(envp[count]);
	return (table);
}