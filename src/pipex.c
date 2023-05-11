/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 18:28:22 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 14:35:53 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	pipex(t_info *info)
{
	int	status;
	int	exit_value;
	int	pid1;
	int	pid2;

	exit_value = 0;
	pid1 = 0;
	pid2 = 0;
	if (pipe(info->fd) == -1)
		exit_error("problem encountered on pipe()\n", info, 1);
	first_child(info, info->fd, &pid1);
	last_child(info, info->fd, &pid2);
	if (waitpid(-1, &status, 0) == pid2)
	{
		if (WIFEXITED(status))
			exit_value = WEXITSTATUS(status);
	}
	close_fds(info);
	return (exit_value);
}

void	close_fds(t_info *info)
{
	if (info->fd[0] > 0)
		close(info->fd[0]);
	if (info->fd[1] > 0)
		close(info->fd[1]);
}

void	close_file_fds(t_info *info)
{
	if (info->infile_fd > 0)
		close(info->infile_fd);
	if (info->outfile_fd > 0)
		close(info->outfile_fd);
}

void	dup_fds(int in_fd, int out_fd, t_info *info)
{
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close_fds(info);
}
