/*
** main.c for rtv1 in /home/buchse_a/Documents/MUL_2013_rtv1
**
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
**
** Started on  Thu Feb 20 15:47:24 2014 Antoine Buchser
** Last update Tue May 27 14:49:16 2014 Antoine Buchser
*/

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <math.h>
#include "rt.h"

static double	lerp(double t, double a, double b)
{
  return (a + t * (b - a));
}

static double	grad(int hash, double x, double y, double z)
{
  int		h;
  double	u;
  double	v;

  h = hash & 15;
  u = (h < 8 || h == 12 || h == 13) ? x : y;
  v = (h < 4 || h == 12 || h == 13) ? y : z;
  return ((((h & 1) == 0) ? u : -u) + (((h & 2) == 0) ? v : -v));
}

double		noise(double x, double y, double z)
{
  int		p[512];
  t_pos		fading;
  int		a;
  int		aa;
  int		ab;
  int		b;
  int		ba;
  int		bb;

  init_perlin(p);
  a = p[(int)floor(x) & 255] + ((int)floor(y) & 255);
  aa = p[a] + ((int)floor(z) & 255);
  ab = p[a + 1] + ((int)floor(z) & 255);
  b = p[((int)floor(x) & 255) + 1] + ((int)floor(y) & 255);
  ba = p[b] + ((int)floor(z) & 255);
  bb = p[b + 1] + ((int)floor(z) & 255);
  get_fading(&fading, &x, &y, &z);
  return (lerp(fading.z, lerp(fading.y, lerp(fading.x, grad(p[aa], x, y, z),
					     grad(p[ba], x - 1, y, z)),
			      lerp(fading.x, grad(p[ab], x, y - 1, z),
				   grad(p[bb], x - 1, y - 1, z))),
	       lerp(fading.y, lerp(fading.x, grad(p[aa + 1], x, y, z - 1),
				   grad(p[ba + 1], x - 1, y, z - 1)),
		    lerp(fading.x, grad(p[ab + 1], x, y - 1, z - 1),
			 grad(p[bb + 1], x - 1, y - 1, z - 1)))));
}
