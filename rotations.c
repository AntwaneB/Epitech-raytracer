/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Sat Jun  7 14:07:56 2014 froehly
*/

#include <stdlib.h>
#include <math.h>
#include "rt.h"

static void	x_rotation(t_pos *pos, double angle)
{
  double	tmp;

  angle = dtor(angle);
  tmp = pos->y;
  pos->y = pos->y * cos(angle) - pos->z * sin(angle);
  pos->z = tmp * sin(angle) + pos->z * cos(angle);
}

static void	y_rotation(t_pos *pos, double angle)
{
  double	tmp;

  angle = dtor(angle);
  tmp = pos->x;
  pos->x = pos->x * cos(angle) + pos->z * sin(angle);
  pos->z = -tmp * sin(angle) + pos->z * cos(angle);
}

static void	z_rotation(t_pos *pos, double angle)
{
  double	tmp;

  angle = dtor(angle);
  tmp = pos->x;
  pos->x = pos->x * cos(angle) - pos->y * sin(angle);
  pos->y = tmp * sin(angle) + pos->y * cos(angle);
}

void	rotation(t_pos *pos, double angle_x,
		 double angle_y, double angle_z)
{
  if (angle_x > ZERO || angle_x < ZERO)
    x_rotation(pos, angle_x);
  if (angle_y > ZERO || angle_y < ZERO)
    y_rotation(pos, angle_y);
  if (angle_z > ZERO || angle_z < ZERO)
    z_rotation(pos, angle_z);
}

void	rev_rotation(t_pos *pos, double angle_x,
		     double angle_y, double angle_z)
{
  if (angle_z > ZERO || angle_z < ZERO)
    z_rotation(pos, -angle_z);
  if (angle_y > ZERO || angle_y < ZERO)
    y_rotation(pos, -angle_y);
  if (angle_x > ZERO || angle_x < ZERO)
    x_rotation(pos, -angle_x);
}
