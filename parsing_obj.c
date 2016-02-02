/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
** 
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
** 
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Wed Jun  4 15:40:13 2014 froehly
*/

#include <stdlib.h>
#include "rt.h"

static void	add_limits(t_obj *elem, t_obj *new)
{
  elem->limits = new->limits;
  elem->limits_s.x = new->limits_s.x;
  elem->limits_s.y = new->limits_s.y;
  elem->limits_s.z = new->limits_s.z;
  elem->limits_e.x = new->limits_e.x;
  elem->limits_e.y = new->limits_e.y;
  elem->limits_e.z = new->limits_e.z;
}

void	add_everything(t_obj *elem, t_obj *new)
{
  elem->type = new->type;
  elem->pos.x = new->pos.x;
  elem->pos.y = new->pos.y;
  elem->pos.z = new->pos.z;
  elem->rot.x = new->rot.x;
  elem->rot.y = new->rot.y;
  elem->rot.z = new->rot.z;
  elem->color.r = new->color.r;
  elem->color.g = new->color.g;
  elem->color.b = new->color.b;
  elem->size = new->size;
  elem->shininess = (new->shininess > 1.0) ? 1.0 : new->shininess;
  elem->checkerboard = new->checkerboard;
  elem->reflex = (new->reflex > 1.0) ? 1.0 : new->reflex;
  elem->transp = (new->transp > 1.0) ? 1.0 : new->transp;
  elem->inter = 0;
  elem->k = -1;
  elem->material = new->material;
  add_limits(elem, new);
  elem->next = NULL;
}
