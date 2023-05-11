/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiple_pipes.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 13:59:53 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 13:58:01 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	create_pipes(t_info *info)
{
	int	i;

	info->pipe_count = (info->cmd_count - 1) * 2;
	info->pipe = malloc(sizeof(int) * info->pipe_count);
	if (!info->pipe)
		exit_error("problem encountered on malloc().\n", info, 1);
	i = 0;
	while (i < info->cmd_count - 1)
	{
		if (pipe(info->pipe + i * 2) < 0)
			exit_error("problem encountered on pipe()\n", info, 1);
		i++;
	}
}

void	first_child(t_info *info, int *pid)
{
	pid[0] = fork();
	if (pid[0] < 0)
	{
		free(pid);
		exit_error("problem encountered on fork()\n", info, 1);
	}
	if (pid[0] == 0)
	{
		check_infile(info);
		dup2(info->infile_fd, STDIN_FILENO);
		dup2(info->pipe[1], STDOUT_FILENO);
		close_pipes(info);
		exec_cmd(info, 0);
	}
}

void	last_child(t_info *info, int *pid)
{
	int	i;

	i = info->cmd_count - 1;
	pid[i] = fork();
	if (pid[i] < 0)
	{
		free(pid);
		exit_error("problem encountered on fork()\n", info, 1);
	}
	if (pid[i] == 0)
	{
		check_outfile(info);
		dup2(info->pipe[(i - 1) * 2], STDIN_FILENO);
		dup2(info->outfile_fd, STDOUT_FILENO);
		close_pipes(info);
		exec_cmd(info, info->cmd_count - 1);
	}
}

void	loop_child(t_info *info, int *pid)
{
	int	i;

	i = 0;
	while (++i < info->cmd_count - 1)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			free(pid);
			exit_error("problem encountered on fork()\n", info, 1);
		}
		if (pid[i] == 0)
		{
			dup2(info->pipe[(i - 1) * 2], STDIN_FILENO);
			dup2(info->pipe[i * 2 + 1], STDOUT_FILENO);
			close_pipes(info);
			exec_cmd(info, i);
		}
	}
}
