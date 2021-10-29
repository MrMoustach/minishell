/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/25 13:13:02 by iharchi           #+#    #+#             */
/*   Updated: 2021/10/29 19:15:55 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static t_var	var_line(char *line)
{
	char	**tab;
	t_var	var;

	tab = split_equals(line);
	var.name = ft_strdup(tab[0]);
	var.line = ft_strdup(line);
	free_tab(tab);
	return (var);
}

char	**get_address(char *var)
{
	int	i;

	i = 0;
	while (g_shell.envp[i])
	{
		if (compare_env(var, g_shell.envp[i]))
			return (&g_shell.envp[i]);
		i++;
	}
	return (NULL);
}

void	print_env(void)
{
	int		i;
	char	**tab;

	i = 0;
	while (g_shell.envp[i])
	{
		if (ft_strchr(g_shell.envp[i], '='))
		{
			tab = split_equals(g_shell.envp[i]);
			printf("declare -x %s=\"%s\"\n", tab[0], tab[1]);
			free_tab(tab);
		}
		else
			printf("%s\n", g_shell.envp[i]);
		i++;
	}
}

void	add_or_modify_var(t_var var)
{
	char	**tab;

	tab = get_address(var.name);
	if (tab)
	{
		free (*tab);
		*tab = var.line;
	}
	else
		ft_addenv(var.line);
}

int	builtin_export(t_token command)
{
	int		i;
	t_var	var;

	if (command.arg_count)
	{
		i = 0;
		while (command.args[i])
		{
			if (command.args[i][0] == '=')
			{
				g_shell.error = 7;
				handle_errors(NULL, command.args[i]);
				return (1);
			}
			var = var_line(command.args[i]);
			add_or_modify_var(var);
			free(var.name);
			i++;
		}
	}
	else
		print_env();
	return (0);
}
