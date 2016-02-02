/*
** event3.c for raytracer in /home/alex/rendu/MUL_2013_rtracer/mul_2013_rtracer
** 
** Made by Alexandre Page
** Login   <page_a@epitech.eu>
** 
** Started on  Thu Jun  5 14:46:29 2014 Alexandre Page
** Last update Fri Jun  6 10:55:08 2014 Alexandre Page
*/

#include <stdio.h>
#include "rt.h"

void	move_letters_next(t_rt *rt)
{
  printf("Camera: x(%f), y(%f), z(%f)\n", rt->camera->pos.x,
	 rt->camera->pos.y, rt->camera->pos.z);
  printf("Camera: rx(%f), ry(%f), rz(%f)\n", rt->camera->rot.x,
	 rt->camera->rot.y, rt->camera->rot.z);
}
