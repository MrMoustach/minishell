/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:43:53 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/20 15:08:17 by iharchi          ###   ########.fr       */
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
		if (!ft_strncmp(tab[0], env, ft_strlen(env) + 1))
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
	char	*tmp;

	i = 0;
	while (state.envp[i])
	{
		if (!ft_strncmp(state.envp[i], env, ft_strlen(env)))
		{
			free(state.envp[i]);;
			tmp = ft_strjoin("=", line); 
			state.envp[i] = ft_strjoin(env, tmp);
			free(tmp);
			break ;
		}
		i++;
	}
}

void	ft_create_env(char *env, char *line)
{
	char	**tab;
	int		i;
	char	*tmp;

	tab = malloc((ft_tablen(state.envp) + 2) * sizeof(char *));
	i = 0;
	while (state.envp[i])
	{
		tab[i] = ft_strdup(state.envp[i]);
		i++;
	}
	tmp = ft_strjoin("=", line);
	tab[i++] = ft_strjoin(env, tmp);
	free (tmp);
	tab[i][0] = '\0';
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