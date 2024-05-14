/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:30:46 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/14 11:56:00 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipix.h"
#include <errno.h>

char	**get_path(char **envp)
{
	int		i;
	char	**path;

	i = 0;
	path = NULL;
	if (!envp)
		return (NULL);
	while (envp[i])
	{
		if (!ft_strncmp(envp[i], "PATH=", 5))
		{
			path = ft_split(envp[i], ':');
			break ;
		}
		i++;
	}
	return (path);
}

void	execute(t_pipix *pipix, char *cmd, char **args, char **envp)
{
	int	fd_cmd;

	(void)pipix;
	execve(cmd, args, envp);
	fd_cmd = open(cmd, __O_DIRECTORY);
	if (fd_cmd == EISDIR)
		perror("is directory\n");
	perror("excve :");
}

void	first_exec(t_pipix *pipix)
{
	if (pipix->fd_in == -1)
		exit(1);
	close(pipix->fd[0]);
	dup2(pipix->fd_in, 0);
	close(pipix->fd_in);
	dup2(pipix->fd[1], 1);
	close(pipix->fd[1]);
}

void	parse(int ac, char **av)
{
	int	i;

	i = 0;
	if (ac == 5)
	{
		if (!check_infile_access(av[1]) && !check_outfile_access(av[ac - 1]))
			perror("pipix: file not found\n");
	}
	else
		perror("pipix: invalid number of arguments\n");
}
