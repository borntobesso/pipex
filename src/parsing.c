/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 19:25:57 by sojung            #+#    #+#             */
/*   Updated: 2022/02/28 15:40:16 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	parse_cmd(t_info *info, char **argv, char **envp)
{
	char	*tmp_path;

	info->infile = ft_strdup(argv[1], info);
	info->cmd[0].cmds = ft_split(argv[2], ' ', info);
	is_slash(&info->cmd[0], argv[2]);
	info->cmd[1].cmds = ft_split(argv[3], ' ', info);
	is_slash(&info->cmd[1], argv[3]);
	info->outfile = ft_strdup(argv[4], info);
	tmp_path = find_path(envp, info);
	if (tmp_path != NULL)
		info->path = ft_split(tmp_path, ':', info);
	free(tmp_path);
	return (0);
}

void	is_slash(t_ps *cmd, char *argv)
{
	if (ft_strncmp(argv, "/", 1) == 0 || ft_strncmp(argv, "./", 2) == 0 || \
		ft_strncmp(argv, "../", 3) == 0)
		cmd->slash = 1;
}

char	*find_path(char **envp, t_info *info)
{
	int		i;
	char	*ret_path;

	i = 0;
	if (envp == NULL)
		return (NULL);
	while (envp[i] != 0)
	{
		if (ft_strncmp(envp[i], "PATH=", 5) == 0)
		{
			ret_path = ft_strdup(envp[i] + 5, info);
			return (ret_path);
		}
		i++;
	}
	return (NULL);
}
