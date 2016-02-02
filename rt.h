/*
** rt.h for rt in /home/giubil_v
**
** Made by victor giubilei
** Login   <giubil_v@epitech.net>
**
** Started on  Wed Jun  4 23:50:44 2014 victor giubilei
** Last update Fri Jun  6 11:00:41 2014 Alexandre Page
*/

#ifndef RT_H_
# define RT_H_

# define NUM_FOUR	65430
# define NUM_THREE	65433
# define NUM_SIX	65432
# define NUM_SEVN	65429
# define NUM_EIGHT	65431
# define NUM_NINE	65434
# define NUM_PLUS	65451
# define NUM_MINUS	65453
# define HELP		104
# define Z		122
# define S		115
# define Q		113
# define A		97
# define D		100
# define E		101
# define N		110
# define SPACE		32
# define ESC		65307
# define CTRL		65507
# define FLUSH		65293

# define ZERO		0.0001
# define WIN_WIDTH	1920
# define WIN_HEIGHT	1080
# define MOVE		54684154
# define ANTIALIASING	0

# define SPHERE		0
# define PLANE		1
# define CONE		2
# define CYLINDRE	3
# define SPOTLIGHT	4

# define MARBLE		1
# define GRAIN		2
# define WOOD		3

# define MULTI_THREAD	1

typedef struct	s_pos
{
  double	x;
  double	y;
  double	z;
}		t_pos;

typedef struct	s_ima
{
  void		*img_ptr;
  char		*firstbyte;
  int		endian;
  int		bpp;
  int		sizeline;
}		t_ima;

typedef struct	s_color
{
  int		r;
  int		g;
  int		b;
}		t_color;

typedef struct	s_obj
{
  int		type;
  int		size;
  double	shininess;
  int		checkerboard;
  double	reflex;
  double	transp;
  double	k;
  double	k2;
  char		inter;
  t_pos		pos;
  t_pos		rot;
  t_pos		p;
  t_pos		n;
  int		limits;
  t_pos		limits_s;
  t_pos		limits_e;
  t_color	color;
  int		material;
  struct s_obj	*next;
}		t_obj;

typedef struct	s_cam
{
  t_pos		pos;
  t_pos		v;
  t_pos		rot;
  t_pos		mov;
  t_pos		dir;
}		t_cam;

typedef struct	s_rt
{
  void		*mlx_ptr;
  void		*win_ptr;
  t_ima		*img;
  t_obj		*objects;
  t_cam		*camera;
  char		*mapfile;
  int		transp_depth;
  int		reflex_depth;
  int		legend;
  double	focale;
  double	ambiant_min;
  int		(**functions)(struct s_rt *rt, t_obj *obj, t_pos *pos);
}		t_rt;

typedef	struct	s_th_container
{
  t_rt		*rt;
  t_pos		*start;
  t_pos		*end;
}		t_th_container;

void		int_to_rgb(t_color *, int);
void		init_color(t_color *);
void		fill_pos(t_pos *, t_pos *, int);
char		**my_str_to_wordtab(char *);

void		cam_init(t_rt*);
void		generate_functions_tab(t_rt*);
void		rt_init(t_rt*, t_ima*, t_cam*);
void		print_progress(void);

void		tmp_set_posrot(t_obj*, char**, int);
void		tmp_set_color(t_obj*, char**, int);
int		is_valid_object(t_obj*, int);
int		get_object_type(char*);
t_obj		*get_all_objects(char*);
void		rt_fill_aa(t_th_container *);
void		rt_fill_noaa(t_th_container *);
void		add_everything(t_obj *, t_obj *);

void		overwrite_camera(t_cam *, t_pos *, t_pos *);
void		backup_camera(t_cam *, t_cam *);
void		backup_pos(t_pos *, t_pos *);
void		obj_backup(t_obj *, t_obj *);
void		set_tmp_camera(t_pos *, t_rt *, t_obj *);

void		manage_light(t_rt *, t_obj *, t_pos *, t_color *);
void		manage_checkerboard(t_obj *, t_color *);
void		manage_transparency(t_rt *, t_obj *, t_pos *, t_color *);

t_obj		*find_closer(t_rt *, t_obj *);

void		find_p(t_rt*, t_obj*, t_pos*);
t_color		*obj_color(t_rt*, t_obj*, t_pos*, t_color *);
int		manage_sphere(t_rt*, t_obj*, t_pos*);
int		manage_plane(t_rt*, t_obj*, t_pos*);
int		manage_cone(t_rt*, t_obj*, t_pos*);
int		manage_cylindre(t_rt*, t_obj*, t_pos*);

void		light_numpad(int, t_rt *);
int		manage_key(int, t_rt*);
int		manage_expose(t_rt*);

void		rotation(t_pos*, double, double, double);
void		rev_rotation(t_pos*, double, double, double);
double		dtor(double);
double		scalar_product(t_pos, t_pos);
void		normalize(t_pos*);

int		rgbandfactor_to_int(t_color *, double);

void		get_spot(t_obj *, t_rt *);

void		my_error(char*);
void		my_perror(char*);
void		free_wordtab(char**);

void		mlx_put_pixel_in_image(t_rt*, int, int, unsigned int);
int		get_lum_object_mult(t_rt *, t_obj *);

int		poscmp(t_pos, t_pos);

/*
** reflexion.c
*/
void		manage_reflexion(t_rt *, t_obj *, t_pos *, t_color *);
t_obj		*is_reflexion(t_rt *, t_obj *, t_pos *);

/*
** shadow.c
*/
void		backup_camera(t_cam *, t_cam *);
void		overwrite_camera(t_cam *, t_pos *, t_pos *);
void		manage_shadow(t_rt *, t_obj *, t_color *);
int		is_shadow(t_rt *, t_obj *, t_pos *);

/*
** transparence.c
*/
void		create_threads(t_rt *);

/*
** limits.c
*/
void		k_permutation(t_obj *);
void		find_limits(t_rt *, t_obj *, t_pos *);

void		limits_parsing(t_obj *, char *, char *);
char		**my_explode(char *);

/*
** perlin.c
*/
void		init_perlin(int [512]);
double		noise(double, double, double);
void		get_fading(t_pos *, double *, double *, double *);

/*
**
*/
void		marble_texture(t_obj *, t_color *);
void		grain_texture(t_obj *, t_color *);
void		wood_texture(t_obj *, t_color *);

/*
** anti_aliasing.c
*/
unsigned int	anti_aliasing(unsigned int, unsigned int,
			      unsigned int, unsigned int);

/*
** medium_color.c
*/
unsigned int	get_medium_color(unsigned int []);
void		decompose_color(unsigned int, t_color *);

/*
** inverse.c
*/
void		my_inverse(char *, t_obj *);
int		my_key_legend(int key, t_rt *rt);

/*
** legend.c
*/
void		my_legend(t_rt *);

/*
** event_dump.c
*/
void		move_letters_next(t_rt *);

/*
** cylindre.c
*/
void		cylindre_find_n(t_obj *);

/*
** cone.c
*/
void		cone_find_n(t_obj *);

/*
** plane.c
*/
void		plane_find_n(t_obj *);

/*
** sphere.c
*/
void		sphere_find_n(t_obj *);
void		create_threads(t_rt *);

/*
** limits.c
*/
void		k_permutation(t_obj *);
void		find_limits(t_rt *, t_obj *, t_pos *);

void		limits_parsing(t_obj *, char *, char *);
char		**my_explode(char *);

/*
** perlin.c
*/
void		init_perlin(int [512]);
double		noise(double, double, double);
void		get_fading(t_pos *, double *, double *, double *);

/*
** anti_aliasing.c
*/
unsigned int	anti_aliasing(unsigned int, unsigned int,
			      unsigned int, unsigned int);

/*
** medium_color.c
*/
unsigned int	get_medium_color(unsigned int []);
void		decompose_color(unsigned int, t_color *);

/*
** inverse.c
*/
void		my_inverse(char *, t_obj *);
int		my_key_legend(int key, t_rt *rt);

/*
** legend.c
*/
void		my_legend(t_rt *);

#endif /* !RT_H_ */
