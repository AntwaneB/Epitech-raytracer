/*
** mlx_put_pixel_in_image.c for mlx_put_pixel_in_image in /home/buchse_a/Documents/Igraph
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Nov  7 14:01:06 2013 Antoine Buchser
** Last update Sat Jun  7 14:20:53 2014 victor giubilei
*/

#include "rt.h"

void    mlx_put_pixel_in_image(t_rt *rt, int x,
			       int y, unsigned int color)
{
  int   i;
  int   color_rgb;

  i = 0;
  while (i < 3)
    {
      if (i == 2)
	color_rgb = (color & 0xFF0000) >> 16;
      else if (i == 1)
	color_rgb = (color & 0xFF00) >> 8;
      else
	color_rgb = color & 0xFF;
      *(rt->img->firstbyte
	+ (y * rt->img->sizeline + x
	   * rt->img->bpp / 8)
	+ i) = color_rgb;
      i++;
    }
}
