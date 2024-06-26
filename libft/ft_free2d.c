/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free2d.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mbentahi <mbentahi@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/18 17:57:37 by mbentahi          #+#    #+#             */
/*   Updated: 2024/05/11 15:08:38 by mbentahi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free2d(char **str)
{
	int	i;

	i = 0;
	if (!str || !*str)
		return (free(str));
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}
