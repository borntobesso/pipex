/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:12:28 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 14:03:48 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	pipex(t_info *info)
{
	int	status;
	int	exit_value;

	status = 0;
	exit_value = 0;
	info->pid = malloc(sizeof(int) * info->cmd_count);
	if (!info->pid)
		exit_error("problem encountered on malloc()\n", info, 1);
	first_child(info, info->pid);
	loop_child(info, info->pid);
	last_child(info, info->pid);
	if (waitpid(-1, &status, 0) == info->pid[info->cmd_count - 1])
	{
		if (WIFEXITED(status))
		exit_value = WEXITSTATUS(status);
	}
	if (info->here_doc == 1)
		unlink(".heredoc");
	return (exit_value);
}

void	close_fds(int *fd)
{
	close(fd[0]);
	close(fd[1]);
}

void	close_file_fds(t_info *info)
{
	if (info->infile_fd > 0)
		close(info->infile_fd);
	if (info->outfile_fd > 0)
		close(info->outfile_fd);
}

void	dup_fds(int in_fd, int out_fd, int *fd)
{
	dup2(in_fd, STDIN_FILENO);
	dup2(out_fd, STDOUT_FILENO);
	close_fds(fd);
}

void	exec_cmd(t_info *info, int index)
{
	close_file_fds(info);
	check_cmd(info, &info->cmd[index]);
	if (execve(info->cmd[index].path, info->cmd[index].cmds, info->envp) == -1)
		exit_error("", info, 1);
}
