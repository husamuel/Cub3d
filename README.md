# Cub3D

**Cub3D** is a dynamic first-person maze exploration game inspired by *Wolfenstein 3D*. Built from the ground up using raycasting techniques, it renders a 3D environment from a 2D map defined in a `.cub` configuration file. This project showcases smooth navigation, textured walls, and customizable aesthetics, delivering an engaging retro gaming experience.

##### Table of Contents  
- [Overview](#overview)  
- [Features](#features)  
- [Installation and Setup](#installation-and-setup)  
- [Controls](#controls)  
- [Development Process](#development-process)  
- [Resources](#resources)  

## Overview

The goal of **cub3d** is to create a visually immersive 3D maze using raycasting, where players can explore custom-designed maps. The project leverages the MiniLibX library to handle graphics and user input, providing a lightweight yet powerful rendering engine.

  ![Cub3D GIF](cub(1).gif)

## Features

- **Customizable Maps**: Define maps via `.cub` files, specifying:
  - Unique wall textures for North, South, East, and West orientations.
  - Floor and ceiling colors using RGB values.
  - 2D map layout (1 = wall, 0 = floor).
  - Player starting position and orientation (N, S, E, W).
- **Real-Time 3D Rendering**: Utilizes raycasting to project a 2D map into a 3D first-person perspective.
- **Smooth Navigation**: Includes player movement with collision detection to prevent walking through walls.
- **Optimized Performance**: Efficient rendering and calculations for a seamless experience.

## Installation and Setup

### Prerequisites
- **MacOS** or **Linux** operating system.
- **MiniLibX** library (included in the repository).
- **GCC** or compatible compiler.

### Steps
1. **Clone the Repository**:
   ```bash
   git clone git@github.com:gabcollet/cub3d.git
   cd cub3d
   ```
2. **Compile and Run**:
   - **MacOS**:
     ```bash
     make
     ./cub3D maps/m_complex.cub
     ```
   - **Linux** (update key bindings in `includes/cub3d.h` if necessary):
     ```bash
     make linux
     ./cub3D maps/m_complex.cub
     ```

**Note**: Ensure the `.cub` map file is valid and located in the `maps/` directory.

## Controls

| Key           | Action            |
|---------------|-------------------|
| ← / →         | Rotate view       |
| W / A / S / D | Move forward/left/backward/right |
| ESC           | Exit game         |

**Note**: Key bindings may vary between MacOS and Linux. Adjust them in `includes/cub3d.h` as needed.

## Development Process

The development of **cub3d** focused on building a robust raycasting engine and core gameplay mechanics. Below are the key steps, with code snippets from the project to illustrate the implementation:

1. **Window Initialization**: Configured the MiniLibX window to serve as the rendering canvas for the 3D environment.
2. **Player Movement with Collision Detection**: Implemented smooth player movement with forward, backward, and strafing capabilities, ensuring collisions with walls were handled accurately. The `move_player` function orchestrates movement, while `check_collision` prevents the player from passing through walls:
   ```c
   void move_player(t_game *game)
   {
       double new_x = game->player.x;
       double new_y = game->player.y;
       move_forward_backward(game, &new_x, &new_y);
       move_strafe(game, &new_x, &new_y);
       if (!check_collision(game, new_x, new_y))
       {
           game->player.x = new_x;
           game->player.y = new_y;
       }
   }

   int check_collision(t_game *game, double new_x, double new_y)
   {
       int map_x = (int)new_x;
       int map_y = (int)new_y;
       if (map_x < 0 || map_x >= game->map->width
           || map_y < 0 || map_y >= game->map->height)
           return (1);
       if (game->map->grid[map_y][map_x] == '1')
           return (1);
       return (0);
   }
   ```
3. **Raycasting Engine**: Developed a raycasting system to render the 3D environment. The `cast_ray` function initializes rays, calculates steps, performs DDA (Digital Differential Analyzer) to detect wall hits, and computes wall distances and heights:
   ```c
   static int cast_ray(t_game *game, int x, t_ray *ray, t_wall *wall)
   {
       if (!init_ray(game, x, ray))
           return (0);
       if (!calc_step_and_dist(ray, game))
           return (0);
       if (!perform_dda(game, ray))
           return (0);
       if (!calc_wall_dist_and_height(game, ray, wall))
           return (0);
       return (1);
   }
   ```
4. **Wall Distance and Height Calculation**: Calculated the perpendicular distance to walls to correct the fish-eye effect and determine wall heights for rendering. The `calc_wall_dist_and_height` function handles this:
   ```c
   static int calc_wall_dist_and_height(t_game *game, t_ray *ray, t_wall *wall)
   {
       if (ray->side == 0)
           wall->perp_dist = (ray->map_x - game->player.x
                   + (1 - ray->step_x) / 2) / ray->dir_x;
       else
           wall->perp_dist = (ray->map_y - game->player.y
                   + (1 - ray->step_y) / 2) / ray->dir_y;
       if (wall->perp_dist <= 0)
           return (0);
       wall->line_height = (int)(game->win_height / wall->perp_dist);
       set_wall_draw_limits(wall, game->win_height);
       return (1);
   }
   ```
5. **Wall Rendering with Textures**: Rendered walls with appropriate textures based on their orientation (North, South, East, West). The `draw_wall_column` function applies textures to each vertical column of the screen:
   ```c
   void draw_wall_column(t_game *game, t_ray *ray, t_wall *wall, int x)
   {
       t_tex *tex = get_texture(game, ray);
       t_tex_info info;
       info.game = game;
       info.ray = ray;
       info.wall = wall;
       info.tex = tex;
       draw_texture_column(&info, x);
   }
   ```
6. **Optimization**: Corrected visual artifacts like fish-eye distortion by using perpendicular distances and refined float-to-integer conversions to ensure smooth wall rendering.

These steps highlight the core mechanics of raycasting and player movement, showcasing the technical foundation of **cub3d**.

## Resources

- [Original Wolfenstein 3D](http://users.atw.hu/wolf3d/) – Inspiration for the project.
- [Raycasting Tutorial](https://lodev.org/cgtutor/raycasting.html) – Comprehensive guide to raycasting techniques.
- [MiniLibX Documentation](https://harm-smits.github.io/42docs/libs/minilibx) – Reference for MiniLibX usage.
- [Wolfenstein 3D Map Renderer](https://www.youtube.com/watch?v=eOCQfxRQ2pY) – Video on map rendering techniques.
- [Super Fast Ray Casting](https://www.youtube.com/watch?v=NbSee-XM7WA&t=1393s) – Tutorial on efficient raycasting.

---

**Thank you for exploring cub3d!**
