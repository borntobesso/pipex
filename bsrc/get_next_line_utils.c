/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/12/03 19:10:52 by sojung            #+#    #+#             */
/*   Updated: 2022/02/22 13:13:50 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	ft_chr_newline(char *buf)
{
	int	i;

	i = 0;
	while (buf[i])
	{
		if (buf[i] == '\n')
			return (1);
		i++;
	}
	return (0);
}

char	*ft_put_line(char *buf)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	result = malloc(sizeof(char) * (i + 1));
	if (!result)
		return (NULL);
	while (j < i)
	{
		result[j] = buf[j];
		j++;
	}
	result[j] = '\0';
	return (result);
}

char	*ft_return_left(char *buf, int index_r)
// saves the rest after the '\n'
{
	char	*r_left;
	int		i;
	int		j;

	i = 0;
	while (buf[i] != '\n')
		i++;
	i++;
	if (buf[i] == '\0')
	{
		free(buf);
		return (NULL);
	}
	r_left = malloc(sizeof(char) * (index_r - i + 1));
	if (!r_left)
		return (NULL);
	j = 0;
	while (buf[i] != '\0')
		r_left[j++] = buf[i++];
	r_left[j] = '\0';
	free(buf);
	return (r_left);
}
