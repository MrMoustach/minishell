/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_args.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:29:15 by iharchi           #+#    #+#             */
/*   Updated: 2021/02/04 11:59:03 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static	int		ft_word(char const *str, int i, int *nbword, int c)
{
	int	escape_flag;

	escape_flag = 0;
	*nbword += 1;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && escape_flag == 0)
			escape_flag = 1;
		else if (str[i] == '\'' && escape_flag == 0)
			escape_flag = 2;
		else if ((str[i] == '"' && escape_flag == 1) || (str[i] == '\'' && escape_flag == 2))
			escape_flag = 0;
		if (str[i] == c && escape_flag == 0)
			break ;
		i++;
	}
	return (i);
}

static	void	ft_free(char **tab, int n)
{
	int	i;

	i = 0;
	while (i > n)
		free(tab[i++]);
	free(tab);
	tab = NULL;
}

static	int		ft_add_word(char **tab, char const *str, int *nbword, int c)
{
	int		wlen;
	int		j;
	char	*tmp;
	int		sv;
	int		escape_flag;

	wlen = 0;
	sv = 0;
	escape_flag = 0;
	while (str[wlen] != '\0')
	{
		if (str[wlen] == '"' && escape_flag == 0)
			escape_flag = 1;
		else if (str[wlen] == '\'' && escape_flag == 0)
			escape_flag = 2;
		else if ((str[wlen] == '"' && escape_flag == 1) || (str[wlen] == '\'' && escape_flag == 2))
			escape_flag = 0;
		if (str[wlen] == c && escape_flag == 0)
			break ;
		wlen++;
	}
	if (!(tmp = (char *)malloc((wlen + 1) * sizeof(char))))
	{
		ft_free(tab, *nbword);
		*nbword = 0;
		return (ft_strlen(str));
	}
	tmp[wlen] = '\0';
	j = 0;
	while (sv < wlen)
	{
		tmp[j] = str[sv++];
		j++;
	}
	tab[*nbword] = tmp;
	*nbword += 1;
	return (wlen);
}

static	void	reset(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char			**ft_split_args(char const *str, char c)
{
	int		i;
	char	**tab;
	int		number_words;

	reset(&i, &number_words);
	if (!str)
		return (NULL);
	while (str[i] != '\0')
		if (str[i] != c)
			i = ft_word(str, i, &number_words, c);
		else
			i++;
	if (!(tab = (char **)malloc((number_words + 1) * sizeof(char *))))
		return (NULL);
	tab[number_words] = 0;
	reset(&i, &number_words);
	while (str[i] != '\0')
		if (str[i] != c)
			i += ft_add_word(tab, str + i, &number_words, c);
		else
			i++;
	if (!number_words && !tab)
		return (NULL);
	return (tab);
}
