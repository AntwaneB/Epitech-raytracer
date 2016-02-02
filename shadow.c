/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 10:33:42 2014 Alexandre Page
*/

#include <stdlib.h>
#include "rt.h"

int	is_shadow(t_rt *rt, t_obj *obj, t_pos *pos)
{
  t_obj	*tmp;
  int	inter;
  t_cam	backup;

  backup_camera(&backup, rt->camera);
  overwrite_camera(rt->camera, &(obj->p), pos);
  tmp = rt->objects;
  while (tmp != NULL)
    {
      if (tmp->type != SPOTLIGHT && tmp != obj)
	rt->functions[tmp->type](rt, tmp, pos);
      if (tmp->k <= 0 || tmp->k >= 1)
	tmp->inter = 0;
      tmp = tmp->next;
    }
  backup_camera(rt->camera, &backup);
  tmp = rt->objects;
  inter = 0;
  while (tmp != NULL && inter == 0)
    {
      if (tmp->type != SPOTLIGHT && tmp != obj)
	inter = tmp->inter;
      tmp = tmp->next;
    }
  return (inter);
}

void	manage_shadow(t_rt *rt, t_obj *obj, t_color *color)
{
  t_pos         l;
  t_obj         spot;

  get_spot(&spot, rt);
  l.x = spot.pos.x - obj->p.x;
  l.y = spot.pos.y - obj->p.y;
  l.z = spot.pos.z - obj->p.z;
  if (is_shadow(rt, obj, &l))
    {
      color->r = (int)(color->r * 0.5);
      color->g = (int)(color->g * 0.5);
      color->b = (int)(color->b * 0.5);
    }
}
