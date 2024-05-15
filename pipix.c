/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipix.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/14 11:52:50 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/15 23:50:37 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipix.h"

void	pipe_handle_helper(t_pipix *pipix, int i, char *cmd, char **args)
{
	if (i == 2)
		first_exec(pipix, cmd, args);
	if (i == pipix->ac - 2)
	{
		if (pipix->fd_out == -1)
		{
			free(cmd);
			ft_free2d(args);
			ft_free2d(pipix->path);
			exit(1);
		}
		close(pipix->fd[1]);
		dup2(pipix->fd[0], 0);
		close(pipix->fd[0]);
		dup2(pipix->fd_out, 1);
		close(pipix->fd_out);
	}
}

void	pipe_handle(t_pipix *pipix, char *cmd, char **args, int i)
{
	pipix->pid[i - 2] = fork();
	if (pipix->pid[i - 2] == 0)
	{
		pipe_handle_helper(pipix, i, cmd, args);
		if (!check_access(cmd))
		{
			ft_putstr_fd("command not found\n", 2);
			free(cmd);
			ft_free2d(args);
			ft_free2d(pipix->path);
			exit(127);
		}
		execute(pipix, cmd, args, pipix->envp);
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

int	cmd_check(char *cmd)
{
	if (cmd && (cmd[0] == '.' || cmd[0] == '/'))
		return (0);
	return (1);
}

char	*cmd_get_helper(char **test, char *tmp, char **path)
{
	if (!cmd_check(test[0]))
	{
		tmp = ft_strdup(test[0]);
		return (tmp);
	}
	if (!path)
	{
		if (test[0] == NULL)
			return (NULL);
		tmp = ft_strdup(test[0]);
		if (access(test[0], F_OK & X_OK) == 0)
			return (tmp);
	}
	return (NULL);
}
