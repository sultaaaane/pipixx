/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipix.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:28:49 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/14 16:27:43 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPIX_H
# define PIPIX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_pipix
{
	char	**envp;
	int		fd[2];
	int		fd_in;
	int		fd_out;
	char	*file_in;
	char	*file_out;
	int		ac;
	int		pid[2];
}			t_pipix;

void		parse(int ac, char **av);
void		pipe_handle(t_pipix *pipix, char *cmd, char **args, int i);
void		first_exec(t_pipix *pipix);
void		execute(t_pipix *pipix, char *cmd, char **args, char **envp);
void		exec_cmd(char **cmd, char **args, char **envp);
int			check_outfile_access(char *file);
int			check_infile_access(char *file);
int			check_access(char *cmd);
char		**get_args(char *cmd);
char		*get_cmd(char **path, char *cmd);
char		**get_path(char **envp);
void		pipe_handle_helper(t_pipix *pipix, int i);
int cmd_check(char *cmd);
#endif