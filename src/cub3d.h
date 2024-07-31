/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rasamad <rasamad@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/18 14:35:46 by jgavairo          #+#    #+#             */
/*   Updated: 2024/07/31 18:51:11 by rasamad          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx-linux/mlx.h"
# include <stdlib.h>
# include <math.h>
# include <stdio.h>
# include "../gnl/get_next_line.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <stdbool.h>
# include <fcntl.h>
# include <string.h>

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
	bool	check;
}	t_color;

typedef struct s_double
{
	bool	no;
	bool	so;
}	t_double;

typedef struct s_texture
{
	void			*img;
	char			*addr;
	char			*path;
	int	 			width;
	int	 			height;
	int	 			bits_per_pixel;
	int	 			line_length;
	int	 			endian;
}					t_texture;

typedef struct s_minimap
{
	int				width;
	int				height;
	int				x;
	int				y;
	int				map_x;
	int				map_y;
	int				minimap_x;
	int				minimap_y;
}					t_minimap;

typedef struct s_raycast
{
	int	 			map_x;
	int	 			map_y;
	double			side_dist_x;
	double			side_dist_y;
	double			delta_dist_x;
	double			delta_dist_y;
	int	 			hit;
	int	 			side;
	double 			camera_x;
	double 			ray_dir_x;
	double 			ray_dir_y;
	int 			x;
	int				y;
	int				d;
	int				tex_num;
	int				tex_x;
	int				tex_y;
	int				draw_end;
	int				line_height;
	int				draw_start;
	double			wall_x;
	double			perp_wall_dist;
	unsigned int	color;
}					t_raycast;

typedef struct s_player
{
	double			pos_x;
	double			pos_y;
	char			dir;
	double			dir_x;
	double			dir_y;
	double			plane_x;
	double			plane_y;
	double			move_speed;
}					 t_player;

typedef struct s_data
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	char			**map;
	int				fd;
	int				bits_per_pixel;
	int				floor_color;
	int				sky_color;
	int				line_length;
	int				endian;
	int				width;
	int				height;
	int				nb_param;
	t_color			sky;
	t_color			floor;
	t_player		player;
	t_raycast		rc;
	t_texture		textures[4];
	t_minimap		minimap;
}					t_data;

	// map_x et map_y :
	//	 La position du joueur en termes de case (cellule) sur la carte de jeu. Par exemple, si le joueur est dans la case (2, 3) de la grille.

	// side_dist_x et side_dist_y :
	//	 Les distances entre la position du joueur et le premier bord (ligne) vertical ou horizontal qu'un rayon va toucher.

	// delta_dist_x et delta_dist_y :
	//	 La distance que le rayon parcourt entre chaque ligne verticale (delta_dist_x) et chaque ligne horizontale (delta_dist_y) de la grille.

	// hit :
	//	 Un indicateur qui devient 1 lorsque le rayon touche un mur.

	// side :
	//	 Indique si le mur touché est vertical (0) ou horizontal (1).

	// camera_x :
	//	 La position horizontale du rayon dans le plan de la caméra, utilisée pour calculer la direction du rayon.

	// ray_dir_x et ray_dir_y :
	//	 La direction du rayon en termes de coordonnées x et y. Par exemple, un rayon allant vers le nord-est aura des ray_dir_x et ray_dir_y positifs ou négatifs.

	// x et y :
	//	 Les coordonnées en pixels sur l'écran pour dessiner les murs.

	// tex_num :
	//	 Le numéro de la texture à utiliser pour le mur touché.

	// tex_x :

	// La position horizontale dans la texture du mur pour un rayon donné.

	// draw_end :

	// La position y sur l'écran où le mur cesse d'être dessiné.

	// line_height :

	// La hauteur du mur en pixels à dessiner sur l'écran.

	// draw_start :

	// La position y sur l'écran où le mur commence à être dessiné.

	// wall_x :

	// La position exacte où le rayon touche le mur, en termes de coordonnées x dans le mur.

	// perp_wall_dist :

	// La distance perpendiculaire entre le joueur et le mur touché par le rayon, utilisée pour corriger l'effet "fisheye".

int		ft_check_arg(t_data *data, char *arg_map);
int		ft_get_texture(t_data *data);
int		ft_strlen_cub(char *s, int choice);
char	*ft_strdup_cub(char *str, int choice);
void	raycasting(t_data *data, t_player *player);
int		ft_fill_color_c(t_data *data, char *gnl, int	i);
int		ft_fill_color_f(t_data *data, char *gnl, int	i);
int		ft_get_color_c(t_data *data, char *gnl);
int		ft_get_color_f(t_data *data, char *gnl);
int		ft_get_no(t_data *data, char *gnl);
int		ft_get_so(t_data *data, char *gnl);
int		ft_get_we(t_data *data, char *gnl);
int		ft_get_ea(t_data *data, char *gnl);
void	ft_free_data(t_data data);

#endif