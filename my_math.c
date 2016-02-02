/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
** 
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
** 
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Thu May 29 15:33:15 2014 Alexandre Page
*/

#include <math.h>
#include "rt.h"

double	dtor(double angle)
{
  return ((M_PI * angle) / 180);
}

double	scalar_product(t_pos v1, t_pos v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

void		normalize(t_pos *v)
{
  double	d;

  d = v->x * v->x + v->y * v->y + v->z * v->z;
  d = sqrt(d);
  v->x /= d;
  v->y /= d;
  v->z /= d;
}
