/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 20:14:18 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 12:23:31 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	check_cmd(t_info *info, t_ps *cmd)
{
	if (cmd->slash == 0)
		set_cmd(info, cmd);
	else
		cmd->path = ft_strdup(cmd->cmds[0], info);
	if (cmd->path == NULL)
	{
		perror(cmd->cmds[0]);
		free_all(info);
		exit(127);
	}
	else if (access(cmd->path, F_OK) == -1)
	{
		perror(cmd->cmds[0]);
		free_all(info);
		exit(127);
	}
	else if (access(cmd->path, X_OK) == -1)
	{
		perror(cmd->cmds[0]);
		free_all(info);
		exit(126);
	}
	return (0);
}

char	*set_cmd(t_info *info, t_ps *cmd)
{
	int		i;
	char	*tmp_path;
	char	*tmp_c_path;

	i = 0;
	if (!info->path)
		return (NULL);
	while (info->path[i])
	{
		tmp_path = ft_strjoin(info->path[i], "/", info);
		tmp_c_path = ft_strjoin(tmp_path, cmd->cmds[0], info);
		if (access(tmp_c_path, F_OK) == 0)
		{
			cmd->path = ft_strdup(tmp_c_path, info);
			free(tmp_path);
			free(tmp_c_path);
			return (cmd->path);
		}
		free(tmp_path);
		free(tmp_c_path);
		i++;
	}
	cmd->path = ft_strdup(cmd->cmds[0], info);
	return (cmd->path);
}
