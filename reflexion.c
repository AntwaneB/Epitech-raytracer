/*
** reflexion.c for raytracer in /home/alex/rendu/MUL_2013_rtracer/mul_2013_rtracer
**
** Made by Alexandre Page
** Login   <page_a@epitech.eu>
**
** Started on  Thu May 29 14:06:14 2014 Alexandre Page
** Last update Sat Jun  7 14:07:21 2014 raphael yazdi
*/

#include <stdlib.h>
#include "rt.h"

t_obj	*is_reflexion(t_rt *rt, t_obj *obj, t_pos *v)
{
  t_obj *tmp;
  t_cam backup;

  backup_camera(&backup, rt->camera);
  overwrite_camera(rt->camera, &(obj->p), v);
  tmp = rt->objects;
  while (tmp != NULL)
    {
      if (tmp->type != SPOTLIGHT && tmp != obj)
        rt->functions[tmp->type](rt, tmp, v);
      if (tmp->k <= 0 || tmp->k >= 1
	  || tmp->type == SPOTLIGHT || tmp == obj)
	tmp->inter = 0;
      tmp = tmp->next;
    }
  backup_camera(rt->camera, &backup);
  return (find_closer(rt, rt->objects));
}

static void	init_director_vector(t_rt *rt, t_obj *obj,
				     t_pos *v, t_pos *l)
{
  if (poscmp(*v, rt->camera->v))
    rotation(v, rt->camera->rot.x, rt->camera->rot.y, rt->camera->rot.z);
  l->x = v->x - 2 * scalar_product(obj->n, *v) * obj->n.x;
  l->y = v->y - 2 * scalar_product(obj->n, *v) * obj->n.y;
  l->z = v->z - 2 * scalar_product(obj->n, *v) * obj->n.z;
  if (poscmp(*v, rt->camera->v))
    rev_rotation(v, rt->camera->rot.x, rt->camera->rot.y, rt->camera->rot.z);
}

void		manage_reflexion(t_rt *rt, t_obj *obj,
				 t_pos *v, t_color *color)
{
  t_pos         l;
  t_obj		*tmp_obj;
  t_color	tmp_color;
  t_obj		backup;
  t_obj		backup_tmp;

  if (obj->reflex && rt->reflex_depth > 0)
    {
      obj_backup(obj, &backup);
      init_director_vector(rt, obj, v, &l);
      if ((tmp_obj = is_reflexion(rt, obj, &l)) != NULL)
	{
	  obj_backup(tmp_obj, &backup_tmp);
	  obj_color(rt, tmp_obj, &l, &tmp_color);
	  obj_backup(&backup_tmp, tmp_obj);
	  color->r = color->r * (1 - obj->reflex) + tmp_color.r * obj->reflex;
	  color->g = color->g * (1 - obj->reflex) + tmp_color.g * obj->reflex;
	  color->b = color->b * (1 - obj->reflex) + tmp_color.b * obj->reflex;
	}
      obj_backup(&backup, obj);
      rt->reflex_depth--;
    }
}
