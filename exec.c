/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/19 21:31:38 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/15 23:51:57 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipix.h"

char	*get_cmd(char **path, char *cmd)
{
	int		i;
	char	*tmp;
	char	*tmp1;
	char	**test;

	i = 0;
	tmp = NULL;
	tmp1 = NULL;
	test = ft_split(cmd, ' ');
	tmp = cmd_get_helper(test, tmp, path);
	if (tmp != NULL)
		return (ft_free2d(test), tmp);
	while (path && path[i])
	{
		tmp1 = ft_strjoin(ft_strdup(path[i]), "/");
		tmp = ft_strjoin(tmp1, test[0]);
		if (access(tmp, F_OK & X_OK) == 0)
			return (ft_free2d(test), tmp);
		free(tmp);
		i++;
	}
	return (ft_free2d(test), tmp);
}

char	**get_args(char *cmd)
{
	int		i;
	char	**args;

	i = 0;
	args = ft_split(cmd, ' ');
	return (args);
}

int	check_access(char *cmd)
{
	if (access(cmd, F_OK | X_OK) == 0)
		return (1);
	return (0);
}

int	check_infile_access(char *file)
{
	if (access(file, F_OK & R_OK) == 0)
		return (1);
	return (0);
}

int	check_outfile_access(char *file)
{
	if (access(file, F_OK & W_OK) == 0)
		return (1);
	return (0);
}
