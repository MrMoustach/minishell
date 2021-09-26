/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: zed <zed@student.42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 11:38:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/26 18:08:56 by zed              ###   ########.fr       */
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
	char	**table;
	int		count;

	count = table_count(g_shell.envp);
	table = malloc(sizeof(char *) * (count + 2));
	table[count + 1] = NULL;
	table[count] = var;
	while (count--)
		table[count] = ft_strdup(g_shell.envp[count]);
	table = sort_env(table);
	free_tab(g_shell.envp);
	g_shell.envp = table;
	sort_env(table);
}

void	ft_delenv(char *var)
{
	char	**table;
	int		count;
	int		flag;

	count = table_count(g_shell.envp);
	table = malloc(sizeof(char *) * (count));
	table[--count] = NULL;
	flag = 1;
	while (count--)
	{
		if (flag && (!ft_strncmp(table[count], var, ft_strlen(var))))
		{
			flag = 0;
			continue ;
		}
		table[count] = ft_strdup(g_shell.envp[count]);
	}
	free_tab(g_shell.envp);
	g_shell.envp = table;
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