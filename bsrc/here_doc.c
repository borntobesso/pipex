/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/21 11:13:30 by sojung            #+#    #+#             */
/*   Updated: 2022/02/28 16:55:02 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

void	is_here_doc(t_info *info, char *arg, int argc)
{
	if (ft_strncmp(arg, "here_doc", 9) == 0)
	{
		info->here_doc = 1;
		info->cmd_count = argc - 4;
	}
	else
	{
		info->here_doc = 0;
		info->cmd_count = argc - 3;
	}
}

void	read_here_doc(t_info *info)
{
	char	*line;
	int		file;
	int		limiter_len;

	file = open(".heredoc", O_RDWR | O_CREAT | O_TRUNC, 0644);
	if (file < 0)
		exit_error("problem encountered on opening a file.\n", info, 1);
	limiter_len = ft_strlen(info->limiter);
	while (1)
	{
		write(1, "pipe heredoc> ", 14);
		line = get_next_line(0);
		if (!line || ft_strncmp(line, info->limiter, limiter_len) == 0)
		{
			free(line);
			break ;
		}
		write(file, line, ft_strlen(line));
		free(line);
	}
	info->infile_fd = open(".heredoc", O_RDONLY);
	if (info->infile_fd < 0)
		perror(info->infile);
	close(file);
}
