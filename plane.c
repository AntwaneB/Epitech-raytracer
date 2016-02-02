/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 10:52:23 2014 Alexandre Page
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

void	plane_find_n(t_obj *obj)
{
  obj->n.x = 0;
  obj->n.y = 0;
  obj->n.z = 1;
}

void	plane_intersection(t_rt *rt, t_obj *obj, t_pos *v)
{
  t_pos	tmp_camera;

  rotation(v, obj->rot.x, obj->rot.y, obj->rot.z);
  tmp_camera.x = rt->camera->pos.x - obj->pos.x;
  tmp_camera.y = rt->camera->pos.y - obj->pos.y;
  tmp_camera.z = rt->camera->pos.z - obj->pos.z;
  rotation(&tmp_camera, obj->rot.x, obj->rot.y, obj->rot.z);
  if (v->z != 0)
    {
      obj->inter = 1;
      obj->k = -tmp_camera.z / v->z;
      obj->k2 = obj->k;
    }
  else
    obj->inter = 0;
  rev_rotation(v, obj->rot.x, obj->rot.y, obj->rot.z);
  rev_rotation(&tmp_camera, obj->rot.x, obj->rot.y, obj->rot.z);
}

int	manage_plane(t_rt *rt, t_obj *obj, t_pos *v)
{
  plane_intersection(rt, obj, v);
  find_p(rt, obj, v);
  find_limits(rt, obj, v);
  plane_find_n(obj);
  return (0);
}
