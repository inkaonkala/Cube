/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yhsu <yhsu@student.hive.fi>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 17:11:17 by yhsu              #+#    #+#             */
/*   Updated: 2024/11/21 17:00:25 by yhsu             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3D.h"

void	err_message_exit(char *message)
{
	if (message)
		ft_putendl_fd(message, 2);
	exit (1);
}

void	err_message(char *message)
{
	ft_putendl_fd("Error ", 2);
	if (message)
		ft_putendl_fd(message, 2);
}
