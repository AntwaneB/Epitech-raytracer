/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Tue Apr 29 15:35:55 2014 Antoine Buchser
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "mlx.h"
#include "rt.h"

void	overwrite_camera(t_cam *dest, t_pos *pos, t_pos *v)
{
  dest->pos.x = pos->x;
  dest->pos.y = pos->y;
  dest->pos.z = pos->z;
  dest->v.x = v->x;
  dest->v.y = v->y;
  dest->v.z = v->z;
}

void	backup_camera(t_cam *new_camera, t_cam *old_camera)
{
  new_camera->pos.x = old_camera->pos.x;
  new_camera->pos.y = old_camera->pos.y;
  new_camera->pos.z = old_camera->pos.z;
  new_camera->v.x = old_camera->v.x;
  new_camera->v.y = old_camera->v.y;
  new_camera->v.z = old_camera->v.z;
  new_camera->rot.x = old_camera->rot.x;
  new_camera->rot.y = old_camera->rot.y;
  new_camera->rot.z = old_camera->rot.z;
}

void	backup_pos(t_pos *pos, t_pos *save)
{
  save->x = pos->x;
  save->y = pos->y;
  save->z = pos->z;
}

void	obj_backup(t_obj *obj, t_obj *backup)
{
  backup->type = obj->type;
  backup->size = obj->size;
  backup->shininess = obj->shininess;
  backup->checkerboard = obj->checkerboard;
  backup->reflex = obj->reflex;
  backup->transp = obj->transp;
  backup->k = obj->k;
  backup->k2 = obj->k2;
  backup->inter = obj->inter;
  backup->pos = obj->pos;
  backup->rot = obj->rot;
  backup->p = obj->p;
  backup->n = obj->n;
  backup->color = obj->color;
  backup->next = obj->next;
  backup->material = obj->material;
}
