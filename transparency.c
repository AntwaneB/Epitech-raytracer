/*
** transparence.c for transparence in /home/yazdi_r/rendu/Igraph/mul_2013_rtracer
**
** Made by raphael yazdi
** Login   <yazdi_r@epitech.net>
**
** Started on  Thu May 29 18:32:37 2014 raphael yazdi
** Last update Thu Jun  5 15:20:53 2014 Alexandre Page
*/

#include <math.h>
#include <stdlib.h>
#include <stdio.h>
#include "rt.h"

static t_obj	*find_closer_transp(t_rt *rt, t_obj *obj)
{
  t_obj		*closer;
  t_obj		*tmp;

  tmp = rt->objects;
  closer = NULL;
  while (tmp)
    {
      if ((closer == NULL || tmp->k < closer->k)
	  && tmp->type != SPOTLIGHT && tmp->k >= 0.0
	  && tmp->inter == 1 && tmp != obj)
	closer = tmp;
      tmp = tmp->next;
    }
  return (closer);
}

static void	init_director_vector(t_rt *rt, t_obj *obj,
				     t_pos *v, t_pos *l)
{
  double	n1;
  double	n2;
  double	n;
  double	cosi;
  double	cosr;

  if (poscmp(rt->camera->v, *v))
    rotation(v, rt->camera->rot.x, rt->camera->rot.y, rt->camera->rot.z);
  n1 = 1.0;
  n2 = 1.0 + obj->transp;
  n = n1 / n2;
  cosi = -scalar_product(obj->n, *v);
  cosr = 1.0 - n * n * (1.0 - cosi * cosi);
  if (cosr > 0.0)
    {
      l->x = (n * v->x) + (n * cosi - sqrtf(cosr)) * obj->n.x;
      l->y = (n * v->y) + (n * cosi - sqrtf(cosr)) * obj->n.y;
      l->z = (n * v->z) + (n * cosi - sqrtf(cosr)) * obj->n.z;
    }
  if (poscmp(rt->camera->v, *v))
    rev_rotation(v, rt->camera->rot.x, rt->camera->rot.y, rt->camera->rot.z);
}

static t_obj	*is_transp(t_rt *rt, t_obj *obj, t_pos *l)
{
  t_obj		*tmp;
  t_cam		backup;

  backup_camera(&backup, rt->camera);
  overwrite_camera(rt->camera, &(obj->p), l);
  tmp = rt->objects;
  while (tmp != NULL)
    {
      tmp->inter = 0;
      if (tmp->type != SPOTLIGHT && tmp != obj)
	{
	  tmp->inter = 1;
	  rt->functions[tmp->type](rt, tmp, l);
	}
      if (tmp->k <= 0.0)
	tmp->inter = 0;
      tmp = tmp->next;
    }
  backup_camera(rt->camera, &backup);
  return (find_closer_transp(rt, obj));
}

void		manage_transparency(t_rt *rt, t_obj *obj,
				    t_pos *v, t_color *color)
{
  t_pos		l;
  t_color	tmp_color;
  t_obj		backup;
  t_obj		*tmp_obj;
  t_obj		backup_tmp;

  if (obj->transp && rt->transp_depth > 0)
    {
      obj_backup(obj, &backup);
      init_director_vector(rt, obj, v, &l);
      init_color(&tmp_color);
      if ((tmp_obj = is_transp(rt, obj, &l)) != NULL)
	{
	  obj_backup(tmp_obj, &backup_tmp);
	  obj_color(rt, tmp_obj, v, &tmp_color);
	  obj_backup(&backup_tmp, tmp_obj);
	}
      color->r = color->r * (1.0 - obj->transp) + tmp_color.r * obj->transp;
      color->g = color->g * (1.0 - obj->transp) + tmp_color.g * obj->transp;
      color->b = color->b * (1.0 - obj->transp) + tmp_color.b * obj->transp;
      obj_backup(&backup, obj);
      rt->transp_depth--;
    }
}
