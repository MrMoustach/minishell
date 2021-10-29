/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/29 14:54:22 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 16:59:13 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_errors_helper(t_token *token, char *message)
{
	if (g_shell.error == 4)
	{
		write (2, "cd: no such file or directory: ", 31);
		write (2, message, ft_strlen(message));
		write (2, "\n", 1);
	}
	else if (g_shell.error == 6)
	{
		write (2, "exit: ", 6);
		write (2, message, ft_strlen(message));
		write (2, ": numeric argument required\n", 28);
	}
	else if (g_shell.error == 7)
	{
		write (2, "minishell: ", 11);
		write (2, message, ft_strlen(message));
		write (2, " is not a valid identifier\n", 27);
	}
	if (g_shell.error == 8)
		write (2, "pwd: Too many arguments\n", 24);
}

void	handle_errors_helper2(t_token *token, char *message)
{
	if (g_shell.error == 9)
	{
		write (2, "unset: ", 7);
		write (2, message, ft_strlen(message));
		write (2, " invalid parameter name\n", 24);
	}
	else if (g_shell.error == 10)
		write (2, message, ft_strlen(message));
	else if (g_shell.error == 11)
	{
		write (2, "Binary doesnt exist : ", 22);
		write (2, message, ft_strlen(message));
		write (2, "\n", 1);
	}
}

void	handle_errors(t_token	*token, char	*message)
{
	g_shell.exit_code = 1;
	if (g_shell.error == 1)
		write (2, "Error: unclosed quotations.\n", 28);
	else if (g_shell.error == 2)
	{
		write (2, "Minishell: Syntax error near : ", 31);
		write (2, token->str, ft_strlen(token->str));
		write (2, "\n", 1);
	}
	else if (g_shell.error == 3)
	{
		write (2, "Minishell: Permission denied or file ", 37);
		write (2, token->args[0], ft_strlen(token->args[0]));
		write (2, " not found.\n", 12);
	}
	handle_errors_helper(token, message);
	handle_errors_helper2(token, message);
}
