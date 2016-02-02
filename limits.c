/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Thu Jun  5 15:07:35 2014 Alexandre Page
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "mlx.h"
#include "rt.h"

void		k_permutation(t_obj *obj)
{
  double	k_tmp;

  if (obj != NULL)
    {
      k_tmp = obj->k;
      obj->k = obj->k2;
      obj->k2 = k_tmp;
    }
}

static void	limits_x(t_rt *rt, t_obj *obj, t_pos *v)
{
  if ((obj->limits_s.x || obj->limits_e.x)
      && (obj->p.x < obj->pos.x + obj->limits_s.x
	  || obj->p.x > obj->pos.x + obj->limits_e.x))
    {
      k_permutation(obj);
      find_p(rt, obj, v);
      if (obj->limits_s.x && obj->limits_e.x
	  && (obj->p.x < obj->pos.x + obj->limits_s.x
	      || obj->p.x > obj->pos.x + obj->limits_e.x))
	{
	  obj->inter = 0;
	  k_permutation(obj);
	}
    }
}

static void	limits_y(t_rt *rt, t_obj *obj, t_pos *v)
{
  if ((obj->limits_s.y || obj->limits_e.y)
      && (obj->p.y < obj->pos.y + obj->limits_s.y
	  || obj->p.y > obj->pos.y + obj->limits_e.y))
    {
      k_permutation(obj);
      find_p(rt, obj, v);
      if ((obj->limits_s.y || obj->limits_e.y)
	  && (obj->p.y < obj->pos.y + obj->limits_s.y
	      || obj->p.y > obj->pos.y + obj->limits_e.y))
	{
	  obj->inter = 0;
	  k_permutation(obj);
	}
    }
}

static void	limits_z(t_rt *rt, t_obj *obj, t_pos *v)
{
  if ((obj->limits_s.z || obj->limits_e.z)
      && (obj->p.z < obj->pos.z + obj->limits_s.z
	  || obj->p.z > obj->pos.z + obj->limits_e.z))
    {
      k_permutation(obj);
      find_p(rt, obj, v);
      if ((obj->limits_s.z || obj->limits_e.z)
	  && (obj->p.z < obj->pos.z + obj->limits_s.z
	      || obj->p.z > obj->pos.z + obj->limits_e.z))
	{
	  obj->inter = 0;
	  k_permutation(obj);
	}
    }
}

void		find_limits(t_rt *rt, t_obj *obj, t_pos *v)
{
  if (obj->limits)
    {
      limits_x(rt, obj, v);
      limits_y(rt, obj, v);
      limits_z(rt, obj, v);
    }
}
