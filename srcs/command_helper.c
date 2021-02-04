/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   command_helper.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:43:53 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 11:11:29 by iharchi          ###   ########.fr       */
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
    }
    return (ft_strdup(""));
}