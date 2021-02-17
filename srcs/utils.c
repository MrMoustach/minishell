/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 10:47:18 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 10:48:11 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void    free_tab(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
        free(tab[i++]);
    free(tab[i]);
    free(tab);
}

int		ft_tablen(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
		i++;
	return(i);
}

char    **dup_tab(char **src)
{
    char    **tab;
    int     i;

    i = 0;
    tab = malloc((ft_tablen(src) + 2) * sizeof(char *));
    while (src[i])
    {
        tab[i] = ft_strdup(src[i]);
        i++;
    }
    tab[i] = '\0';
    return (tab);
}