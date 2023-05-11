/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   child.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/28 15:45:38 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 14:37:12 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	first_child(t_info *info, int *fd, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		exit(1);
	if (*pid == 0)
	{
		if (access(info->infile, F_OK) < 0)
		{
			perror(info->infile);
			exit_error("", info, 1);
		}
		else if (access(info->infile, R_OK) < 0)
		{
			perror(info->infile);
			exit_error("", info, 1);
		}
		info->infile_fd = open(info->infile, O_RDWR);
		if (info->infile_fd < 0)
			perror(info->infile);
		dup_fds(info->infile_fd, fd[1], info);
		close_file_fds(info);
		check_cmd(info, &info->cmd[0]);
		if (execve(info->cmd[0].path, info->cmd[0].cmds, info->envp) == -1)
			exit_error("", info, 1);
	}
}

void	last_child(t_info *info, int *fd, int *pid)
{
	*pid = fork();
	if (*pid < 0)
		exit(1);
	if (*pid == 0)
	{
		if (!access(info->outfile, F_OK))
		{
			if (access(info->outfile, W_OK) < 0 || \
				access(info->outfile, R_OK) < 0)
			{
				perror(info->outfile);
				exit_error("", info, 1);
			}
		}
		info->outfile_fd = open(info->outfile, O_RDWR | O_CREAT | O_TRUNC, \
		0644);
		if (info->outfile_fd < 0)
			perror(info->outfile);
		dup_fds(fd[0], info->outfile_fd, info);
		close_file_fds(info);
		check_cmd(info, &info->cmd[1]);
		if (execve(info->cmd[1].path, info->cmd[1].cmds, info->envp) == -1)
			exit_error("", info, 1);
	}
}
