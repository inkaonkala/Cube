/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:44:27 by iniska            #+#    #+#             */
/*   Updated: 2024/10/11 10:47:32 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	main(int arc, char **arv)
{
	if (arc == 2)
	{
		printf("Off to the game we go!\n");
		//parsing(arv[1]);
	}
	else
		printf("Give me a .cub to work with!\n");
	return (0);
}