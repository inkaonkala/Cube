/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iniska <iniska@student.hive.fi>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 10:49:17 by iniska            #+#    #+#             */
/*   Updated: 2024/10/11 12:49:17 by iniska           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE_H
# define CUBE_H

# include <stdio.h>
# include <math.h>
# include <stdbool.h>
# include <unistd.h>

//typedef struct	t_mlx
//{
//
//}

// parsing

void	exiting(char *map, char str);
void	parsing(char **arv);

// map_validators

bool	valid_map(char *map);
bool	valid_colours(char *map);
bool	valid_pic(char *map);


#endif