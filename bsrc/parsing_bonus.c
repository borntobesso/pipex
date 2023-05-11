/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:10:55 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 13:57:51 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	parse_cmd(t_info *info, char **argv, char **envp)
{
	char	*tmp_path;
	int		i;

	if (info->here_doc == 0)
		info->infile = ft_strdup(argv[1], info);
	else
		info->limiter = ft_strjoin(argv[1], "\n", info, 0);
	i = 0;
	while (i < info->cmd_count)
	{
		info->cmd[i].cmds = ft_split(argv[i + 2], ' ', info);
		is_slash(&info->cmd[i], argv[i + 2]);
		i++;
	}
	info->outfile = ft_strdup(argv[info->cmd_count + 2], info);
	tmp_path = find_path(envp, info);
	if (tmp_path != NULL)
		info->path = ft_split(tmp_path, ':', info);
	free(tmp_path);
	return (0);
}

void	is_slash(t_ps *cmd, char *arg)
{
	if (ft_strncmp(arg, "/", 1) == 0 || ft_strncmp(arg, "./", 2) == 0 || \
		ft_strncmp(arg, "../", 3) == 0)
		cmd->slash = 1;
}

int	check_slash(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->cmd_count)
	{
		if (info->cmd[i].slash == 0)
			return (1);
		i++;
	}
	return (0);
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
