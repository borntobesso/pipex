/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/10 10:59:48 by sojung            #+#    #+#             */
/*   Updated: 2022/02/28 15:47:39 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	int		ret_val;

	ret_val = 0;
	if (argc == 5)
	{
		ft_memset(&info, 0, sizeof(t_info));
		info.envp = envp;
		parse_cmd(&info, argv, envp);
		ret_val = pipex(&info);
		free_all(&info);
		close_file_fds(&info);
		close(STDIN_FILENO);
		close(STDOUT_FILENO);
		close(STDERR_FILENO);
	}
	else
		exit_error("wrong input count.\n", &info, 0);
	return (ret_val);
}
