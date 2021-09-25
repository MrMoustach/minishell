/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 11:36:47 by iharchi           #+#    #+#             */
/*   Updated: 2021/09/25 12:11:43 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

 #include "minishell.h"

void	builtin_pwd(t_token command)
{
	char	*str;
	 if (command.arg_count)
	{
		printf("pwd: Too many arguments\n");
		return ;
	}
	str = ft_getenv("PWD");
	if (str)
	{
		printf("%s\n", str);
		free(str);
	}
}