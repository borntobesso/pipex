/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:11:11 by sojung            #+#    #+#             */
/*   Updated: 2022/02/22 13:20:55 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

static char	*ft_strdup_g(char *s)
{
	char	*tab;
	int		i;

	tab = malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!tab)
		return (NULL);
	i = 0;
	while (s[i])
	{
		tab[i] = s[i];
		i++;
	}
	tab[i] = '\0';
	return (tab);
}
// leak ok (frees in joinleft)

static char	*ft_strjoin_g(char *left, char *buf)
{
	char	*res;
	int		i;
	int		j;

	res = malloc(sizeof(char) * (ft_strlen(left) + ft_strlen(buf) + 1));
	if (!res)
		return (NULL);
	i = 0;
	while (left != NULL && left[i])
	{
		res[i] = left[i];
		i++;
	}
	j = 0;
	while (buf != NULL && buf[j])
	{
		res[i] = buf[j];
		i++;
		j++;
	}
	res[i] = '\0';
	return (res);
}

char	*ft_clean(char **left, char *buf)
{
	char	*result;

	result = ft_put_line(buf);
	*left = ft_return_left(buf, ft_strlen(buf));
	return (result);
}
// leak ok (frees result in main, frees buf in return_left)

char	*ft_joinleft(char **left, int fd)
{
	char	*result;
	char	*new;
	char	*join;

	new = ft_strdup_g(*left);
	free(*left);
	*left = NULL;
	join = get_next_line(fd);
	result = ft_strjoin_g(new, join);
	free(join);
	free(new);
	return (result);
}
// leak ok (frees result in main)

char	*get_next_line(int fd)
{
	char		*buf;
	static char	*left;
	int			index_r;

	if (left != NULL)
	{
		if (ft_chr_newline(left) == 1)
			return (ft_clean(&left, left));
		return (ft_joinleft(&left, fd));
	}
	buf = malloc(sizeof(char) * (BUFFER_SIZE + 1));
	if (!buf)
		return (NULL);
	index_r = read(fd, buf, BUFFER_SIZE);
	if (index_r == -1 || index_r == 0)
	{
		free(left);
		free(buf);
		return (NULL);
	}
	buf[index_r] = '\0';
	if (ft_chr_newline(buf) == 1)
		return (ft_clean(&left, buf));
	else
		return (ft_joinleft(&buf, fd));
}
// leak ok (frees the previous left or buf in ft_clean)
// else, return value freed in main
