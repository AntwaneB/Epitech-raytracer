/*
** multispot.c for multispot in /home/giubil_v
**
** Made by victor giubilei
** Login   <giubil_v@epitech.net>
**
** Started on  Wed Mar 26 11:16:10 2014 victor giubilei
** Last update Fri Jun  6 10:52:53 2014 raphael yazdi
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

void	int_to_rgb(t_color *color, int change_color)
{
  color->r = (change_color & 0xFF0000) >> 16;
  color->g = (change_color & 0xFF00) >> 8;
  color->b = change_color & 0xFF;
}

static void	set_cam_null(t_obj *obj)
{
  while (obj)
    {
      if (obj->type == SPOTLIGHT)
	obj->size = 1;
      obj = obj->next;
    }
}

int		get_lum_object_mult(t_rt *rt, t_obj *obj)
{
  t_color	buffer;
  t_color	ret_calc;
  t_obj		*save;

  init_color(&buffer);
  save = rt->objects;
  set_cam_null(save);
  while (save != NULL)
    {
      if (save->type == SPOTLIGHT)
	{
	  rt->transp_depth = 1;
	  rt->reflex_depth = 1;
	  obj_color(rt, obj, &(rt->camera->v), &ret_calc);
	  buffer.r += ret_calc.r;
	  buffer.g += ret_calc.g;
	  buffer.b += ret_calc.b;
	  save->size = 0;
	}
      save = save->next;
    }
  buffer.r = (buffer.r > 255) ? 255 : buffer.r;
  buffer.g = (buffer.g > 255) ? 255 : buffer.g;
  buffer.b = (buffer.b > 255) ? 255 : buffer.b;
  return (rgbandfactor_to_int(&buffer, 1));
}
