#include "collisions.h"
#include "game.h"
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>

#define WIDTH 480
#define HEIGHT 320

void check_target_collisions(game_t *game){
    for(int i = 0; i < game->num_player_bullets; i++){
        for (int j = 0; j < game->current_level.num_targets; j++){
            if (game->player_bullets[i].position.y == game->targets[j].base.position.y + game->targets[j].height - 3 &&
                (game->player_bullets[i].position.x == game->targets[j].base.position.x || 
                game->player_bullets[i].position.x == game->targets[j].base.position.x + game->targets[j].width - 1)){
                game->targets[j].health--;
            }
        }
    }
}
