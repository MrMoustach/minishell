/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 20:48:01 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 20:48:17 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	int_sig_handler(int sig)
{
	(void)sig;
	if (g_shell.pid == 1)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		g_shell.last_status = 1;
	}
}

void	quit_sig_handler(int sig)
{
	(void)sig;
	if (g_shell.pid == 1)
	{
		rl_on_new_line();
		rl_redisplay();
	}
}
