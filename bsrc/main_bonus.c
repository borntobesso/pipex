/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:10:26 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 13:57:57 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/pipex_bonus.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_info	info;
	int		ret_val;

	ft_memset(&info, 0, sizeof(t_info));
	ret_val = 0;
	if (argc >= 5)
	{
		is_here_doc(&info, argv[1], argc);
		info.cmd = malloc(sizeof(t_ps) * info.cmd_count);
		if (!info.cmd)
			exit_error("problem encountered on malloc()\n", &info, 1);
		ft_memset(info.cmd, 0, sizeof(t_ps) * info.cmd_count);
		create_pipes(&info);
		info.envp = envp;
		parse_cmd(&info, argv + info.here_doc, info.envp);
		ret_val = pipex(&info);
		free_all(&info);
		close_file_fds(&info);
	}
	else
		exit_error("wrong input count.\n", &info, 0);
	return (ret_val);
}
