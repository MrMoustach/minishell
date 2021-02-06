/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:43:53 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 12:19:55 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char *ft_get_env(char *env)
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

char *get_next_word(char *s)
{
    int i;
    char *ret;

    i = 0;
    while (s[i] && s[i] != ' ' && s[i] != '"' && s[i] != '\'')
       i++;
    ret = ft_substr(s, 0, i);
    return (ret);
}

void    free_command(void *com)
{
    t_command   command;

    command = *(t_command *)com;
    free_tab(command.args);
}