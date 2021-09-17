/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iharchi <iharchi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/18 03:29:15 by iharchi           #+#    #+#             */
/*   Updated: 2021/06/26 17:52:24 by iharchi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_word(char const *str, int i, int *nbword, int c)
{
	*nbword += 1;
	while (str[i] != c && str[i] != '\0')
		i++;
	return (i);
}

static int	ft_add_word(char **tab, char const *str, int *nbword, int c)
{
	int		wlen;
	int		j;
	char	*tmp;
	int		sv;

	wlen = 0;
	sv = 0;
	while (str[wlen] != c && str[wlen] != '\0')
		wlen++;
	tmp = (char *)malloc((wlen + 1) * sizeof(char));
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

static void	reset(int *i, int *j)
{
	*i = 0;
	*j = 0;
}

char	**ft_split(char const *str, char c)
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
	tab = (char **)malloc((number_words + 1) * sizeof(char *));
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
