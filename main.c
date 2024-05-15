/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:28:25 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/15 18:37:01 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipix.h"

void	pipix_init(t_pipix *pipix, char **envp, char **args, int ac)
{
	pipix->envp = envp;
	pipix->fd_in = open(args[1], O_RDONLY);
	pipix->ac = ac;
	pipix->path = get_path(envp);
	if (pipix->fd_in == -1)
		perror("pipix ");
	pipix->file_in = args[1];
	pipix->fd_out = open(args[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipix->fd_out == -1)
		perror("pipix ");
	pipix->file_out = args[ac - 1];
}

void	main_helper(t_pipix *pipix, int ac, char **av, char **path)
{
	int		i;
	char	*cmd;
	char	**args;

	cmd = NULL;
	args = NULL;
	i = 2;
	while (i < ac - 1)
	{
		cmd = get_cmd(path, av[i]);
		args = get_args(av[i]);
		pipe_handle(pipix, cmd, args, i);
		ft_free2d(args);
		free(cmd);
		i++;
	}
}

int	main(int ac, char **av, char **env)
{
	t_pipix	pipix;
	int		status;
	int		i;

	if (ac != 5)
	{
		ft_putstr_fd("pipix: usage: pipix [file] [cmd] [cmd] [file]\n", 2);
		return (1);
	}
	else
	{
		pipix_init(&pipix, env, av, ac);
		
		pipe(pipix.fd);
		main_helper(&pipix, ac, av, pipix.path);
		i = 0;
		while (i < 2)
		{
			waitpid(pipix.pid[i], &status, 0);
			i++;
		}
		ft_free2d(pipix.path);
	}
	return ((((status) >> 8) & 0x0000ff));
}
