/*
** my_str_to_wordtab.c for my_str_to_wordtab in /home/buchse_a/Documents/Piscine-C-Jour_08/ex_04
** 
** Made by Antoine Buchser
** Login   <buchse_a@epitech.net>
** 
** Started on  Wed Oct  9 11:01:05 2013 Antoine Buchser
** Last update Thu Jan 16 16:39:50 2014 Antoine Buchser
*/

#include <stdlib.h>

static int	is_tos(char c)
{
  if (c == ' ' || c == 9)
    return (1);
  else
    return (0);
}

static int	my_nb_sep(char *str)
{
  int		i;
  int		nb_sep;

  i = 1;
  nb_sep = 0;
  while (str[i])
    {
      if (is_tos(str[i]) && !is_tos(str[i - 1]))
	nb_sep = nb_sep + 1;
      i++;
    }
  if (str[i] == '\0' && !is_tos(str[i - 1]))
    nb_sep++;
  return (nb_sep);
}

static char	*my_tab_fill_line(char **tab, char *str, int len, int i)
{
  int		j;

  if ((tab[i] = malloc((len + 1) * sizeof(**tab))) == NULL)
    return (NULL);
  j = 0;
  while (!is_tos(str[j]) && str[j] != '\0')
    {
      tab[i][j] = str[j];
      j++;
    }
  tab[i][j] = '\0';
  return (NULL);
}

int	only_space(char *str)
{
  int	i;

  i = 0;
  while (str[i])
    {
      if (str[i] != ' ' && str[i] != '\t')
	return (0);
      i++;
    }
  return (1);
}

char	**my_str_to_wordtab(char *str)
{
  char	**tab;
  int	i;
  int	j;
  int	nb_sep;

  if (only_space(str))
    return (NULL);
  nb_sep = my_nb_sep(str);
  if ((tab = malloc((nb_sep + 1) * sizeof(*tab))) == NULL)
    return (NULL);
  i = 0;
  while (i < nb_sep)
    {
      while (is_tos(str[0]) && str[0] != '\0')
	str++;
      j = 0;
      while (!is_tos(str[j]) && str[j] != '\0')
	j++;
      my_tab_fill_line(tab, str, j, i);
      str = str + j;
      i++;
    }
  tab[i] = NULL;
  return (tab);
}
