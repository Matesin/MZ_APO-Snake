#ifndef __GAME_H__
#define __GAME_H__
#include "game_graphics.h"
#include "ingame_menu.h"
#include "font_types.h"
#include "collisions.h"
#include "constants.h"

#include <stdbool.h>
#include <stdio.h>
#define BACKGROUND_COLOR {255, 255, 255}
//Space Invaders Structs and functions definitions
extern font_descriptor_t* fdes;
typedef struct game_object {
    point_t position;
    void (*update) (struct game_object *self, graphics_object_t *graphics);
    void (*render) (struct game_object *self, graphics_object_t *graphics);
} game_object_t;


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

typedef struct player_ship {
    game_object_t base;
    int width;
    int height;
    int health;
    void (*update) (struct player_ship *self, input_state_t *input);
    void (*render) (struct player_ship *self, graphics_object_t *graphics);
} player_ship_t;

typedef struct projectile {
    game_object_t base;
    int width;
    int height; //fixed size for all projectiles ?
    int damage;
    void (*update) (struct projectile *self, graphics_object_t *graphics);
} projectile_t;

typedef struct enemy_ship {
    game_object_t base;
    int width;
    int height;
    int health;
    void (*update) (struct enemy_ship *self, graphics_object_t *graphics);
} enemy_ship_t;

typedef struct target{
    game_object_t base;
    int width;
    int height;
    int health;
    void (*update) (struct target *self, graphics_object_t *graphics);
} target_t;

typedef struct level{
    int num_targets;
    int level_num;
    bool completed;
} level_t;

typedef struct game{
    game_settings_t settings;
    player_ship_t player;
    input_state_t input;
    graphics_object_t graphics;
    game_object_t *enemies;
    game_object_t *player_bullets;
    game_object_t *enemy_bullets;
    target_t *targets;
    level_t current_level;
    int num_enemies;
    int num_player_bullets;
    int num_enemy_bullets;
    void (*init) (struct game *self);
    void (*update) (struct game *self);
    void (*render) (struct game *self);
    void (*destroy) (struct game *self);
    void (*fire_bullet) (struct game *self, game_object_t *shooter);
}game_t;

void update_player_ship(player_ship_t* self, input_state_t* input);
void render_player_ship(player_ship_t* self, graphics_object_t* graphics);
void handle_input(input_state_t* self);
void game_loop(graphics_object_t* graphics, game_t* game);

#endif // __GAME_H__