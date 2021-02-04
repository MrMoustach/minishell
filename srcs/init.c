/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/03 17:30:38 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 10:43:04 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void	init_shell(char *envp[])
{
	char *cwd;
	
	cwd = NULL;
	cwd = getcwd(cwd, 0);
	state.cwd = cwd;
	state.envp = envp;
}

void refresh_shell()
{
	free(state.cwd);
	state.cwd = NULL;
	state.cwd = getcwd(state.cwd, 0);
}