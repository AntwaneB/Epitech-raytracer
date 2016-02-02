/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 10:55:53 2014 Alexandre Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

void	cylindre_find_n(t_obj *obj)
{
  obj->n.x = obj->p.x - obj->pos.x;
  obj->n.y = obj->p.y - obj->pos.y;
  obj->n.z = obj->p.z - obj->pos.z;
}

void		cylindre_intersection(t_rt *rt, t_obj *obj, t_pos *v)
{
  double	a;
  double	b;
  double	c;
  t_pos		tmp_camera;

  rotation(v, obj->rot.x, obj->rot.y, obj->rot.z);
  tmp_camera.x = rt->camera->pos.x - obj->pos.x;
  tmp_camera.y = rt->camera->pos.y - obj->pos.y;
  tmp_camera.z = rt->camera->pos.z - obj->pos.z;
  rotation(&tmp_camera, obj->rot.x, obj->rot.y, obj->rot.z);
  a = pow(v->x, 2) + pow(v->y, 2);
  b = 2.0 * (tmp_camera.x * v->x + tmp_camera.y * v->y);
  c = pow(tmp_camera.x, 2) + pow(tmp_camera.y, 2) - pow(obj->size, 2);
  if ((pow(b, 2) - 4.0 * a * c) >= 0)
    {
      obj->inter = 1;
      obj->k = (-b + sqrt(pow(b, 2.0) - 4.0 * a * c)) / (2.0 * a);
      obj->k2 = (-b - sqrt(pow(b, 2.0) - 4.0 * a * c)) / (2.0 * a);
      k_permutation((obj->k > obj->k2) ? obj : NULL);
    }
  else
    obj->inter = 0;
  rev_rotation(v, obj->rot.x, obj->rot.y, obj->rot.z);
  rev_rotation(&tmp_camera, obj->rot.x, obj->rot.y, obj->rot.z);
}

int	manage_cylindre(t_rt *rt, t_obj *obj, t_pos *v)
{
  cylindre_intersection(rt, obj, v);
  find_p(rt, obj, v);
  find_limits(rt, obj, v);
  cylindre_find_n(obj);
  return (0);
}
