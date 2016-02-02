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
#include "mlx.h"
#include "rt.h"

int	g_permutation[] =
  {
    230, 190, 33, 59, 3, 59, 75, 18, 81, 203,
    195, 233, 104, 39, 224, 55, 97, 134, 123, 245,
    212, 161, 235, 155, 216, 175, 9, 32, 6, 105,
    45, 252, 117, 6, 45, 40, 189, 63, 100, 28,
    247, 75, 168, 207, 187, 227, 81, 185, 32, 62,
    56, 211, 191, 20, 180, 149, 175, 159, 158, 246,
    136, 148, 77, 110, 100, 46, 154, 246, 216, 34,
    220, 6, 254, 171, 236, 149, 110, 126, 34, 27,
    63, 214, 85, 145, 9, 104, 221, 110, 230, 110,
    147, 171, 107, 160, 206, 192, 178, 53, 103, 164,
    83, 230, 181, 207, 101, 234, 145, 58, 129, 250,
    82, 93, 190, 77, 209, 47, 180, 156, 102, 40,
    124, 30, 231, 65, 174, 140, 175, 242, 97, 29,
    148, 50, 46, 138, 238, 121, 44, 10, 150, 192,
    243, 86, 227, 126, 156, 165, 174, 172, 191, 176,
    78, 194, 115, 174, 156, 183, 81, 88, 240, 3,
    112, 229, 32, 159, 104, 14, 135, 3, 82, 10,
    251, 38, 198, 146, 212, 128, 219, 221, 235, 10,
    42, 163, 151, 60, 202, 30, 177, 13, 83, 3,
    144, 245, 223, 141, 13, 237, 3, 113, 127, 109,
    217, 234, 191, 108, 249, 173, 37, 98, 122, 245,
    136, 72, 244, 119, 64, 149, 129, 109, 38, 66,
    182, 143, 145, 199, 173, 20, 90, 27, 254, 181,
    216, 182, 192, 169, 228, 145, 140, 169, 213, 36,
    121, 236, 132, 102, 31, 43, 73, 207, 151, 157,
    250, 88, 121, 251, 242, 121
  };

void		init_perlin(int p[512])
{
  int		i;

  i = 0;
  while (i < 256)
    {
      p[256 + i] = p[i] = g_permutation[i];
      i++;
    }
}

static double	fade(double t)
{
  return (t * t * t * (t * (t * 6 - 15) + 10));
}

void	get_fading(t_pos *fading, double *x, double *y, double *z)
{
  *x -= floor(*x);
  *y -= floor(*y);
  *z -= floor(*z);
  fading->x = fade(*x);
  fading->y = fade(*y);
  fading->z = fade(*z);
}