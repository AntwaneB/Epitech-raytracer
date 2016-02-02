/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 10:53:50 2014 Alexandre Page
*/

#include <stdlib.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

void		marble_texture(t_obj *obj,
			       t_color *final_color)
{
  int		i;
  double	noise_amount;

  noise_amount = 0.0;
  i = 0;
  while (++i < 10)
    noise_amount += (1.0 / i) * fabs(noise(i * 0.05 * obj->p.x,
					   i * 0.15 * obj->p.y,
					   i * 0.05 * obj->p.z));
  noise_amount = 0.5 * sinf((obj->p.x + obj->p.y) * 0.05 + noise_amount) + 0.5;
  final_color->r = final_color->r + noise_amount * 25
    + 233 * (1 - noise_amount);
  final_color->g = final_color->g + noise_amount * 25
    + 233 * (1 - noise_amount);
  final_color->b = final_color->b + noise_amount * 25
    + 233 * (1 - noise_amount);
}

void		grain_texture(t_obj *obj,
			      t_color *final_color)
{
  int		i;
  double	noise_amount;

  noise_amount = 0.0;
  i = 0;
  while (++i < 10)
    noise_amount += (1.0 / i) * fabs(noise(i * 0.05 * obj->p.x,
					   i * 0.05 * obj->p.y,
					   i * 0.05 * obj->p.z));
  noise_amount = (noise_amount > 1.0) ? 1.0 : noise_amount;
  final_color->r = final_color->r + noise_amount * 0
    + 255 * (1 - noise_amount);
  final_color->g = final_color->g + noise_amount * 0
    + 255 * (1 - noise_amount);
  final_color->b = final_color->b + noise_amount * 0
    + 255 * (1 - noise_amount);
}

void		wood_texture(t_obj *obj,
			     t_color *final_color)
{
  double	grain;
  double	n;
  double	scale;

  scale = 50.0;
  grain = fabs(noise(obj->p.x * scale, obj->p.y * scale,
		     obj->p.z * scale)) * 20.0;
  n = grain - (int)(grain);
  int_to_rgb(final_color, 0x462E01 * n + 0x02F1B0C * (1.0 - n));
}
