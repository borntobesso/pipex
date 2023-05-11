/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 15:17:32 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 14:52:20 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>

/*
/		|STRUCTURES|
*/

typedef struct s_ps
{
	char	**cmds;
	int		slash;
	char	*path;
}	t_ps;

typedef struct s_info
{
	char	*infile;
	char	*outfile;
	char	**envp;
	t_ps	cmd[2];
	char	**path;
	int		infile_fd;
	int		outfile_fd;
	int		fd[2];
}	t_info;

/*
/		|UTILITY FUNCTIONS|
*/

void	*ft_memset(void *b, int c, int len);
int		ft_strncmp(char *s1, char *s2, int n);
int		ft_strlen(char *str);
char	*ft_strdup(char *s, t_info *info);
int		word_count(char *s, char c);
char	*word_malloc(char *s, char c, t_info *info);
char	**ft_split(char *s, char c, t_info *info);
char	*ft_strjoin(char *s1, char *s2, t_info *info);

/*
/		|ERROR / FREE FUNCTIONS|
*/

void	exit_error(char *msg, t_info *info, int flag);
void	free_split(char **tab);
void	free_all(t_info *info);

/*
/		|PARSING FUNCTIONS|
*/

int		parse_cmd(t_info *info, char **argv, char **envp);
void	is_slash(t_ps *cmd, char *argv);
char	*find_path(char **envp, t_info *info);

/*
/		|PARSING CHECK FUNCTIONS|
*/

void	check_parsing(t_info *info);
int		check_cmd(t_info *info, t_ps *cmd);
char	*set_cmd(t_info *info, t_ps *cmd);

/*
/		|PIPEX FUNCTIONS|
*/

int		pipex(t_info *info);
void	close_fds(t_info *info);
void	close_file_fds(t_info *info);
void	dup_fds(int in_fd, int out_fd, t_info *info);
void	first_child(t_info *info, int *fd, int *pid);
void	last_child(t_info *info, int *fd, int *pid);

#endif
