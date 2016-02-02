/*
** medium_color.c for raytracer in /home/alex/rendu/MUL_2013_rtracer/mul_2013_rtracer
** 
** Made by Alexandre Page
** Login   <page_a@epitech.eu>
** 
** Started on  Mon Jun  2 13:34:11 2014 Alexandre Page
** Last update Mon Jun  2 17:32:43 2014 raphael yazdi
*/

#include "rt.h"

unsigned int     get_medium_color(unsigned int color[8])
{
  t_color               decomposed_color[8];
  t_color               final_color;
  int                   i;

  i = -1;
  while (++i < 8)
    decompose_color(color[i], &(decomposed_color[i]));
  final_color.r = (int)((((decomposed_color[0]).r + (decomposed_color[1]).r
			  + (decomposed_color[2]).r + (decomposed_color[3]).r)
			 + (decomposed_color[4].r) + (decomposed_color[5]).r
			 + (decomposed_color[6]).r + (decomposed_color[7]).r) / 8.0);
  final_color.g = (int)((((decomposed_color[0]).g + (decomposed_color[1]).g
			  + (decomposed_color[2]).g + (decomposed_color[3]).g)
			 + (decomposed_color[4].g) + (decomposed_color[5]).g
			 + (decomposed_color[6]).g + (decomposed_color[7]).g) / 8.0);
  final_color.b = (int)((((decomposed_color[0]).b + (decomposed_color[1]).b
			  + (decomposed_color[2]).b + (decomposed_color[3]).b)
			 + (decomposed_color[4].b) + (decomposed_color[5]).b
			 + (decomposed_color[6]).b + (decomposed_color[7]).b) / 8.0);
  return (rgbandfactor_to_int(&(final_color), 1));
}

void             decompose_color(unsigned int color, t_color *to_fill)
{
  to_fill->r = (color & 0xFF0000) >> 16;
  to_fill->g = (color & 0x00FF00) >> 8;
  to_fill->b = color & 0x0000FF;
}

