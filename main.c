/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/17 13:28:25 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/10 14:32:16 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipix.h"

void pipix_init(t_pipix *pipix,char **envp,char **args,int ac)
{
	pipix->envp = envp;
	pipix->fd_in = open(args[1],O_RDONLY);
	pipix->ac = ac;
	if (pipix->fd_in == -1)
	{
		ft_putstr_fd("pipix: ",2);
		ft_putstr_fd(args[1],2);
		ft_putstr_fd(": No such file or directory\n",2);
	}
	pipix->file_in = args[1];
	pipix->fd_out = open(args[ac - 1], O_CREAT | O_RDWR | O_TRUNC, 0644);
	if (pipix->fd_out == -1)
	{
		ft_putstr_fd("pipix: ",2);
		ft_putstr_fd(args[ac - 1],2);
		ft_putstr_fd(": No such file or directory\n",2);
	}
	pipix->file_out = args[ac - 1];
}


int main(int ac,char **av,char **env)
{
	t_pipix pipix;
	char **path;
	char *cmd;
	char **args;
	int status;
	int i;
	
	args = NULL;
	cmd	= NULL;
	path = NULL;
	if (ac != 5)
	{
		ft_putstr_fd("pipix: usage: pipix [file] [cmd] [file]\n",2);
		return (1);
	}
	else
	{
		pipix_init(&pipix,env,av,ac);
		parse(ac,av);
		path = get_path(pipix.envp);
		i = 2;
		pipe(pipix.fd);
		
		while (i < ac - 1)
		{
			
			cmd = get_cmd(path,av[i]);
			args = get_args(av[i]);
			pipe_handle(&pipix,cmd,args,i);
			ft_free2d(args);
			i++;
		}
		i = 0;
		while (i < 2)
		{
			waitpid(pipix.pid[i],&status,0);
			i++;
		}
		if (path)
			ft_free2d(path);
	}
}
