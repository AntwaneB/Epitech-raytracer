/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 10:56:33 2014 Alexandre Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

void	find_p(t_rt *rt, t_obj *obj, t_pos *v)
{
  obj->p.x = rt->camera->pos.x + v->x * obj->k;
  obj->p.y = rt->camera->pos.y + v->y * obj->k;
  obj->p.z = rt->camera->pos.z + v->z * obj->k;
}

int	rgbandfactor_to_int(t_color *color, double factor)
{
  int	color_res;

  color_res = 0;
  color_res |= (int)(color->r * factor) % 256;
  color_res <<= 8;
  color_res |= (int)(color->g * factor) % 256;
  color_res <<= 8;
  color_res |= (int)(color->b * factor) % 256;
  return (color_res);
}

static void	init_spot(t_obj *spot)
{
  spot->type = SPOTLIGHT;
  spot->pos.x = 0;
  spot->pos.y = 0;
  spot->pos.z = 0;
  spot->color.r = 255;
  spot->color.g = 255;
  spot->color.b = 255;
}

void	get_spot(t_obj *spot, t_rt *rt)
{
  t_obj	*obj;

  init_spot(spot);
  obj = rt->objects;
  while (obj != NULL)
    {
      if (obj->type == SPOTLIGHT && obj->size == 1)
	{
	  spot->type = obj->type;
	  spot->pos.x = obj->pos.x;
	  spot->pos.y = obj->pos.y;
	  spot->pos.z = obj->pos.z;
	  spot->color = obj->color;
	  return ;
	}
      obj = obj->next;
    }
}

t_color		*obj_color(t_rt *rt, t_obj *obj,
			   t_pos *v, t_color *final_color)
{
  final_color->r = obj->color.r;
  final_color->g = obj->color.g;
  final_color->b = obj->color.b;
  if (obj->material == MARBLE)
    marble_texture(obj, final_color);
  else if (obj->material == GRAIN)
    grain_texture(obj, final_color);
  else if (obj->material == WOOD)
    wood_texture(obj, final_color);
  manage_checkerboard(obj, final_color);
  manage_shadow(rt, obj, final_color);
  manage_light(rt, obj, v, final_color);
  manage_reflexion(rt, obj, v, final_color);
  manage_transparency(rt, obj, v, final_color);
  return (final_color);
}
