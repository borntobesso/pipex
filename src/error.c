/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/11 16:54:11 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 14:22:55 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

void	exit_error(char *msg, t_info *info, int flag)
{
	if (flag == 1)
	{
		free_all(info);
		close_fds(info);
		close_file_fds(info);
	}
	write(2, msg, ft_strlen(msg));
	close(STDIN_FILENO);
	close(STDOUT_FILENO);
	close(STDERR_FILENO);
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

void	free_all(t_info *info)
{
	if (info->infile)
		free(info->infile);
	if (info->outfile)
		free(info->outfile);
	if (info->path)
		free_split(info->path);
	if (info->cmd[0].cmds)
		free_split(info->cmd[0].cmds);
	if (info->cmd[1].cmds)
		free_split(info->cmd[1].cmds);
	if (info->cmd[0].path)
		free(info->cmd[0].path);
	if (info->cmd[1].path)
		free(info->cmd[1].path);
}
