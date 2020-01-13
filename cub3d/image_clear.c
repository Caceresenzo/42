/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_clear.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ecaceres <ecaceres@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/18 18:43:35 by ecaceres          #+#    #+#             */
/*   Updated: 2019/11/18 18:43:35 by ecaceres         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "image.h"

void
	image_clear(t_image *image)
{
	ft_bzero(image->pic, image->height * image->width * image->bpp);
}
