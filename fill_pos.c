/*
** fill_pos.c for raytracer in /home/alex/rendu/MUL_2013_rtracer/mul_2013_rtracer
** 
** Made by Alexandre Page
** Login   <page_a@epitech.eu>
** 
** Started on  Thu Jun  5 15:18:02 2014 Alexandre Page
** Last update Thu Jun  5 15:19:20 2014 Alexandre Page
*/

#include "rt.h"

void     fill_pos(t_pos *start, t_pos *end, int i)
{
  if (ANTIALIASING == 1)
    {
      if (i < 4)
        start->y = -(WIN_HEIGHT / 2) * 4 + WIN_HEIGHT / 2;
      else
        start->y = WIN_HEIGHT / 2;
      end->y = start->y + (WIN_HEIGHT / 2) * 4;
      if (i >= 4)
        i -= 4;
      start->x = -WIN_WIDTH * 2 + WIN_WIDTH / 2 + i * WIN_WIDTH;
      end->x = start->x + WIN_WIDTH;
    }
  else
    {
      start->y = (i < 4) ? 0 : WIN_HEIGHT / 2;
      end->y = (i < 4) ? WIN_HEIGHT / 2 : WIN_HEIGHT;
      i = (i >= 4) ? i - 4 : i;
      start->x = (i * WIN_WIDTH) / 4;
      end->x = ((i + 1) * WIN_WIDTH) / 4;
    }
}
