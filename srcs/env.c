/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 11:38:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/26 17:50:42 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name)
{
	char 	*tmp;
	int		i;
	char	**sp;
	char	*ret;

	i = 0;
	while (g_shell.envp[i])
	{
		sp = ft_split(g_shell.envp[i], '=');
		if (!ft_strncmp(sp[0], name, ft_strlen(name)))
		{
			ret = ft_strdup(sp[1]);
			free_tab(sp);
			return (ret);
		}
		free_tab(sp);
		i++;
	}
	// FIXME: Null made add too many ifs in the expansion probably not worth it
	return (NULL);
}

void	ft_addenv(char *var)
{
	
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