/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:43:53 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/08 14:36:29 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*ft_get_env(char *env)
{
	char    **tab;
	int     i;
	char    *home;

	if (env == NULL)
		return (NULL);
	i = 0;
	home = NULL;
	while (state.envp[i])
	{
		tab = ft_split(state.envp[i], '=');
		if (!ft_strncmp(tab[0], env, ft_strlen(env)))
		{
			home = ft_strdup(tab[1]);
			free_tab(tab);
			return (home);
		}
		i++;
		free_tab(tab);
	}
	return (ft_strdup(""));
}

void	ft_set_env(char	*env, char *line)
{
	int		i;

	i = 0;
	while (state.envp[i])
	{
		if (!ft_strncmp(state.envp[i], env, ft_strlen(env)))
		{
			free(state.envp[i]);
			state.envp[i] = ft_strdup(line);
			break ;
		}
		i++;
	}
}

void	ft_create_env(char	*line)
{
	char	**tab;
	int		i;

	tab = malloc((ft_tablen(state.envp) + 2) * sizeof(char *));
	i = 0;
	while (state.envp[i])
	{
		tab[i] = ft_strdup(state.envp[i]);
		i++;
	}
	tab[i++] = ft_strdup(line);
	tab[i] = NULL;
	free_tab(state.envp);
	state.envp = tab;
}

char	*get_next_word(char *s)
{
	int i;
	char *ret;

	i = 0;
	while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'' && s[i] != '/' && s[i] != '\\')
	   i++;
	ret = ft_substr(s, 0, i);
	return (ret);
}

void	free_command(void *com)
{
	t_command   command;

	command = *(t_command *)com;
	free_tab(command.args);
	free(com);
}