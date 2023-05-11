/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_parsing_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:11:22 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 12:56:38 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	check_infile(t_info *info)
{
	if (!info->here_doc && access(info->infile, F_OK) < 0)
	{
		perror(info->infile);
		exit_error("", info, 1);
	}
	else if (!info->here_doc && access(info->infile, R_OK) < 0)
	{
		perror(info->infile);
		exit_error("", info, 1);
	}
	if (info->here_doc == 1)
		read_here_doc(info);
	else
		info->infile_fd = open(info->infile, O_RDWR);
	if (info->infile_fd < 0)
		perror(info->infile);
}

void	check_outfile(t_info *info)
{
	if (!access(info->outfile, F_OK))
	{
		if (access(info->outfile, W_OK) < 0 || access(info->outfile, R_OK) < 0)
		{
			perror(info->outfile);
			exit_error("", info, 1);
		}
	}
	if (info->here_doc == 1)
		info->outfile_fd = open(info->outfile, O_RDWR | O_CREAT | O_APPEND, \
		0644);
	else
		info->outfile_fd = open(info->outfile, O_RDWR | O_CREAT | O_TRUNC, \
		0644);
	if (info->outfile_fd < 0)
		perror(info->outfile);
}

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
		tmp_path = ft_strjoin(info->path[i], "/", info, 0);
		tmp_c_path = ft_strjoin(tmp_path, cmd->cmds[0], info, 0);
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
