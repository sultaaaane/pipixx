/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:46 by mbentahi          #+#    #+#             */
/*   Updated: 2024/04/29 17:44:36 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipix.h"

char **get_path(char **envp)
{
	int		i;
	char	**path;
	i = 0;
	
	path = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i],"PATH=",5))
		{
			path = ft_split(envp[i],':');
			break;
		}	
		i++;
	}
	return (path);
}

char *get_cmd(char **path,char *cmd)
{
	int i;
	char *tmp;
	char	*tmp1;
	char **test;
	
	i = 0;
	test = ft_split(cmd,' ');
	while (path && path[i])
	{	
		tmp1 = ft_strjoin(ft_strdup(path[i]),"/");
		tmp = ft_strjoin(tmp1,test[0]);
		if (access(tmp,F_OK & X_OK) == 0)
			return (ft_free2d(test),tmp);
		free(tmp1);
		free(tmp);
		i++;
	}
	return (ft_free2d(test),NULL);
}

char **get_args(char *cmd)
{
	int i;
	char **args;
	
	i = 0;
	args = ft_split(cmd,' ');
	return (args);
}

int check_access(char *cmd)
{
	if (access(cmd,F_OK & X_OK) == 0)
		return (1);
	return (0);
}

int check_infile_access(char *file)
{
	if (access(file,F_OK & R_OK ) == 0)
		return (1);
	return (0);
}

int check_outfile_access(char *file)
{
	if (access(file,F_OK & W_OK ) == 0)
		return (1);
	return (0);
}

void execute(char *cmd,char **args,char **envp)
{
	if (execve(cmd,args,envp) == -1)
	{
		free(cmd);
		ft_free2d(args);
		perror("excve");
	}
}

void first_exec(t_pipix *pipix)
{
	if (pipix->fd_in == -1)
		exit(1);
	close(pipix->fd[0]);
	dup2(pipix->fd_in, 0);
	close(pipix->fd_in);
	dup2(pipix->fd[1], 1);
	close(pipix->fd[1]);
}

void pipe_handle(t_pipix *pipix,char *cmd,char **args,int i)
{
	pipix->pid[i-2] = fork();
	if (pipix->pid[i - 2] == 0)
	{
		if (i == 2)
			first_exec(pipix);
		if (i == pipix->ac - 2)
		{
			if (pipix->fd_out == -1)
				exit(1);
			close(pipix->fd[1]);
			dup2(pipix->fd[0], 0);
			close(pipix->fd[0]);
			dup2(pipix->fd_out,1);
			close(pipix->fd_out);
		}
		if (!check_access(cmd))
		{
			ft_putstr_fd("command not found\n",2);
			free(cmd);
			ft_free2d(args);
			exit(127);
		}
		execute(cmd,args,pipix->envp);
	}
	else
	{
		if (i != 2)
			(close(pipix->fd[0]), close(pipix->fd_out));	
		if (i != pipix->ac - 2)
		{
			close(pipix->fd_in);
			close(pipix->fd[1]);
		}
	}
}
void parse(int ac,char **av)
{
	int i;

	i = 0;
	if (ac == 5)
	{
		if (!check_infile_access(av[1]) && !check_outfile_access(av[ac - 1]))
			perror("pipix: file not found\n");
	}
	else
		perror("pipix: invalid number of arguments\n");
}
