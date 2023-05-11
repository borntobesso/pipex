/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:13:17 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 12:51:45 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	exit_error(char *msg, t_info *info, int flag)
{
	if (flag == 1)
		close_file_fds(info);
	free_all(info);
	write(2, msg, ft_strlen(msg));
	exit(1);
}

void	free_split(char **tab)
{
	int	i;

	i = 0;
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab[i]);
	free(tab);
}

void	free_cmd(t_ps *cmd, t_info *info)
{
	int	i;

	i = 0;
	while (i < info->cmd_count)
	{
		free(cmd[i].path);
		free_split(cmd[i].cmds);
		i++;
	}
	free(cmd);
}

void	close_pipes(t_info *info)
{
	int	i;

	i = 0;
	while (i < info->pipe_count)
	{
		close(info->pipe[i]);
		i++;
	}
	free(info->pipe);
	info->pipe = NULL;
}

void	free_all(t_info *info)
{
	if (info->infile)
		free(info->infile);
	if (info->outfile)
		free(info->outfile);
	if (info->path)
		free_split(info->path);
	if (info->cmd)
		free_cmd(info->cmd, info);
	if (info->limiter)
		free(info->limiter);
	if (info->pipe)
		close_pipes(info);
	if (info->pid)
		free(info->pid);
}
