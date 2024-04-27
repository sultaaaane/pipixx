/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipix.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:28:49 by mbentahi          #+#    #+#             */
/*   Updated: 2024/04/27 20:21:06 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPIX_H
#define PIPIX_H

# include "ft_printf/ft_printf.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/wait.h>

typedef struct s_pipix
{
	char	**envp;
	int		fd[2];
	int		fd_in;
	int		fd_out;
	int		ac;
	int		pid[2];
}					t_pipix;

void parse(int ac,char **av,char **envp);
void pipe_handle(t_pipix *pipix,char *cmd,char **args,int i);
void first_exec(t_pipix *pipix);
void execute(char *cmd,char **args,char **envp);
void exec_cmd(char **cmd, char **args, char **envp);
int check_outfile_access(char *file);
int check_infile_access(char *file);
int check_access(char *cmd);
char **get_args(char *cmd);
char *get_cmd(char **path,char *cmd);
char **get_path(char **envp);



#endif