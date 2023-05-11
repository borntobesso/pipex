/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:12:54 by sojung            #+#    #+#             */
/*   Updated: 2022/02/22 17:17:37 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	*ft_memset(void *b, int c, int len)
{
	char	*str;
	int		i;

	str = b;
	i = 0;
	while (i < len)
	{
		str[i] = c;
		i++;
	}
	return (b);
}

int	ft_strncmp(char *s1, char *s2, int n)
{
	int				i;
	unsigned char	*str1;
	unsigned char	*str2;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	if (n == 0)
		return (0);
	i = 0;
	while (str1[i] && str2[i] && i < n - 1)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
		i++;
	}
	return (str1[i] - str2[i]);
}

int	ft_strlen(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (0);
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *s, t_info *info)
{
	int		len;
	char	*res;

	len = 0;
	while (s[len])
		len++;
	res = (char *)malloc(sizeof(char) * (len + 1));
	if (res == NULL)
		exit_error("Problem encountered on malloc.\n", info, 1);
	res[len] = '\0';
	while (len > 0)
	{
		res[len - 1] = s[len - 1];
		len--;
	}
	return (res);
}

char	*ft_strjoin(char *s1, char *s2, t_info *info, int flag)
{
	int		i;
	int		j;
	char	*res;

	res = (char *)malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (res == NULL)
		exit_error("Problem encountered on malloc.\n", info, 1);
	i = 0;
	j = 0;
	while (j < ft_strlen(s1))
		res[i++] = s1[j++];
	j = 0;
	while (j < ft_strlen(s2))
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	res[i] = '\0';
	if (flag == 1)
		free(s1);
	return (res);
}
