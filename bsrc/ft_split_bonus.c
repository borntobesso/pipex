/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:11:49 by sojung            #+#    #+#             */
/*   Updated: 2022/02/17 16:22:48 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	word_count(char *s, char c)
{
	int	count;

	count = 0;
	while (*s)
	{
		while (*s && *s == c)
			s++;
		if (*s && *s != c)
		{
			count++;
			while (*s && *s != c)
				s++;
		}
	}
	return (count);
}

char	*word_malloc(char *s, char c, t_info *info)
{
	int		len;
	int		i;
	char	*word;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	word = (char *)malloc(sizeof(char) * (len + 1));
	if (word == NULL)
		exit_error("Problem encountered on malloc.\n", info, 1);
	i = 0;
	while (*s && *s != c)
	{
		word[i] = *(s++);
		i++;
	}
	word[i] = '\0';
	return (word);
}

char	**ft_split(char *s, char c, t_info *info)
{
	char	**res;
	int		i;
	int		j;

	res = (char **)malloc(sizeof(char *) * (word_count(s, c) + 1));
	if (res == NULL)
		exit_error("Problem encountered on malloc\n", info, 1);
	i = 0;
	j = 0;
	while (s[j])
	{
		while (s[j] == c)
			j++;
		if (s[j] && s[j] != c)
		{
			res[i] = word_malloc(&s[j], c, info);
			i++;
			while (s[j] && s[j] != c)
				j++;
		}
	}
	res[i] = 0;
	return (res);
}
