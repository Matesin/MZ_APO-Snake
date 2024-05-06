#ifndef __GAME_H__
#define __GAME_H__
#include "game_graphics.h"
#include <stdbool.h>
//Space Invaders Structs and functions definitions

typedef struct game_object {
    point_t position;
    void (*update) (struct game_object *self, graphics_object_t *graphics);
    void (*render) (struct game_object *self, graphics_object_t *graphics);
} game_object_t;

typedef struct player_ship {
    game_object_t base;
    int width;
    int height;
} player_ship_t;

typedef struct game_settings{
    int player_lives;
    int player_score;
    int player_speed;
    int enemy_speed;
    int enemy_bullet_speed;
    int player_bullet_speed;
    int player_fire_rate;
    int enemy_fire_rate;
} game_settings_t;

typedef struct input_state {
    bool up;
    bool down;
    bool left;
    bool right;
    bool fire;
    bool quit;
    bool pause;

    void (*handle_input) (struct input_state *self);
} input_state_t;

typedef struct game{
    game_settings_t settings;
    player_ship_t player;
    input_state_t input;
    graphics_object_t graphics;
    game_object_t *enemies;
    game_object_t *player_bullets;
    game_object_t *enemy_bullets;
    int num_enemies;
    int num_player_bullets;
    int num_enemy_bullets;
    void (*init) (struct game *self);
    void (*update) (struct game *self);
    void (*render) (struct game *self);
    void (*destroy) (struct game *self);
}game_t;


#endif // __GAME_H__