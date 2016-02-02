/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Fri Jun  6 10:54:49 2014 Alexandre Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

static double	manage_diffuse_light(t_rt *rt, t_obj *obj,
				     t_obj *spot)
{
  t_pos		l;
  double	num;
  double	den1;
  double	den2;
  double	cos_a;

  l.x = spot->pos.x - obj->p.x;
  l.y = spot->pos.y - obj->p.y;
  l.z = spot->pos.z - obj->p.z;
  num = obj->n.x * l.x + obj->n.y * l.y + obj->n.z * l.z;
  den1 = sqrt(pow(l.x, 2.0) + pow(l.y, 2.0) + pow(l.z, 2.0));
  den2 = sqrt(pow(obj->n.x, 2.0) + pow(obj->n.y, 2.0)
	      + pow(obj->n.z, 2.0));
  cos_a = num / (den1 * den2);
  cos_a = (cos_a < rt->ambiant_min) ? rt->ambiant_min : cos_a;
  return (cos_a);
}

static double	manage_specular_light(t_obj *obj,
				      t_obj *spot, t_pos *v)
{
  t_pos		r;
  t_pos		l;
  double	spec;
  t_pos		v_tmp;

  l.x = spot->pos.x - obj->p.x;
  l.y = spot->pos.y - obj->p.y;
  l.z = spot->pos.z - obj->p.z;
  normalize(&(obj->n));
  r.x = l.x - 2 * scalar_product(obj->n, l) * obj->n.x;
  r.y = l.y - 2 * scalar_product(obj->n, l) * obj->n.y;
  r.z = l.z - 2 * scalar_product(obj->n, l) * obj->n.z;
  normalize(&r);
  backup_pos(v, &v_tmp);
  normalize(&v_tmp);
  spec = powf(scalar_product(v_tmp, r), obj->shininess * 200.0);
  if (spec > 0.0 && spec <= 1.0)
    return (spec);
  else
    return (0.0);
}

void		manage_light(t_rt *rt, t_obj *obj,
			     t_pos *pos, t_color *color)
{
  t_obj		spot;
  double	spec;
  double	diff;

  get_spot(&spot, rt);
  diff = manage_diffuse_light(rt, obj, &spot);
  if (obj->shininess > 0.0)
    spec = manage_specular_light(obj, &spot, pos);
  else
    spec = 0.0;
  diff = (diff < rt->ambiant_min) ? rt->ambiant_min : diff;
  color->r = color->r * (1 - obj->shininess) + spot.color.r * obj->shininess;
  color->g = color->g * (1 - obj->shininess) + spot.color.g * obj->shininess;
  color->b = color->b * (1 - obj->shininess) + spot.color.b * obj->shininess;
  color->r += 255 * spec;
  color->g += 255 * spec;
  color->b += 255 * spec;
  color->r = color->r * diff;
  color->g = color->g * diff;
  color->b = color->b * diff;
}
