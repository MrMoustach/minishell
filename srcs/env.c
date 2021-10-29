/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omimouni <omimouni@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 11:38:32 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 17:16:54 by omimouni         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_getenv(char *name)
{
	int		i;
	char	**sp;

	i = 0;
	while (g_shell.envp[i])
	{
		if (compare_env(name, g_shell.envp[i]))
		{
			sp = split_equals(g_shell.envp[i]);
			free (sp[0]);
			free (sp);
			return (sp[1]);
		}
		i++;
	}
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
	int		i;

	count = table_count(g_shell.envp);
	table = malloc(sizeof(char *) * (count));
	i = 0;
	flag = 0;
	while (g_shell.envp[i])
	{
		if (!flag && compare_env(var, g_shell.envp[i]))
		{
			flag = 1;
			i++;
			continue ;
		}
		table[i - flag] = ft_strdup(g_shell.envp[i]);
		i++;
	}
	table[i - flag] = NULL;
	free_tab(g_shell.envp);
	g_shell.envp = table;
}

void	ft_modenv(char *name, char *line)
{
	int		i;

	i = 0;
	while (g_shell.envp[i])
	{
		if (compare_env(name, g_shell.envp[i]))
		{
			free (g_shell.envp[i]);
			g_shell.envp[i] = line;
			break ;
		}
		i++;
	}
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
