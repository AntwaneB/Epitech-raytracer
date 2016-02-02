/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Wed Mar 26 11:34:11 2014 Antoine Buchser
*/

#include "rt.h"

void	light_numpad(int key, t_rt *rt)
{
  if (key == NUM_PLUS)
    rt->ambiant_min += (rt->ambiant_min + 0.1 <= 1.0) ? 0.1 : 0;
  else if (key == NUM_MINUS)
    rt->ambiant_min -= (rt->ambiant_min - 0.1 >= 0.0) ? 0.1 : 0;
}
