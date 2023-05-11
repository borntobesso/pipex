/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sojung <sojung@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/17 15:09:29 by sojung            #+#    #+#             */
/*   Updated: 2022/03/08 12:39:53 by sojung           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_BONUS_H
# define PIPEX_BONUS_H

# include <stdio.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <string.h>
# include <unistd.h>
# include <errno.h>
# define BUFFER_SIZE 1

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
	int		here_doc;
	char	*limiter;
	int		cmd_count;
	int		pipe_count;
	t_ps	*cmd;
	int		*pipe;
	char	**path;
	int		infile_fd;
	int		outfile_fd;
	int		*pid;
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
char	*ft_strjoin(char *s1, char *s2, t_info *info, int flag);

/*
/		|ERROR / FREE FUNCTIONS|
*/

void	exit_error(char *msg, t_info *info, int flag);
void	free_split(char **tab);
void	free_all(t_info *info);
void	free_cmd(t_ps *cmd, t_info *info);
void	close_pipes(t_info *info);

/*
/		|PARSING FUNCTIONS|
*/

int		parse_cmd(t_info *info, char **argv, char **envp);
void	is_slash(t_ps *cmd, char *argv);
int		check_slash(t_info *info);
char	*find_path(char **envp, t_info *info);

/*
/		|PARSING CHECK FUNCTIONS|
*/

void	check_infile(t_info *info);
void	check_outfile(t_info *info);
void	check_parsing(t_info *info);
int		check_cmd(t_info *info, t_ps *cmd);
char	*set_cmd(t_info *info, t_ps *cmd);

/*
/		|PIPEX FUNCTIONS|
*/

int		pipex(t_info *info);
void	close_fds(int *fd);
void	close_file_fds(t_info *info);
void	dup_fds(int in_fd, int out_fd, int *fd);
void	exec_cmd(t_info *info, int index);

/*
/		|HERE_DOC INPUT FUNCTIONS|
*/

void	is_here_doc(t_info *info, char *arg, int argc);
void	read_here_doc(t_info *info);

/*
/		|MULTIPLE PIPES FUNCTIONS|
*/

void	create_pipes(t_info *info);
void	first_child(t_info *info, int *pid);
void	last_child(t_info *info, int *pid);
void	loop_child(t_info *info, int *pid);

/*
/		|GET_NEXT_LINE FUNCTIONS|
*/

char	*get_next_line(int fd);
int		ft_chr_newline(char *buf);
char	*ft_put_line(char *buf);
char	*ft_return_left(char *buf, int index_r);
char	*ft_clean(char **left, char *buf);
char	*ft_joinleft(char **left, int fd);

#endif
