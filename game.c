#include "game.h"
#include "ingame_menu.c"
color_t chosen_color = {255, 255, 255}; //update this value throughout the game

void update_player_ship(player_ship_t* self, input_state_t* input){
    if (input->up){
        self->base.position.y -= PLAYER_SPEED;
    }
    if (input->down){
        self->base.position.y += PLAYER_SPEED;
    }
    if (input->left){
        self->base.position.x -= PLAYER_SPEED;
    }
    if (input->right){
        self->base.position.x += PLAYER_SPEED;
    }
}

void render_player_ship(player_ship_t* self, graphics_object_t* graphics){
    point_t vertices[] = {{self->base.position.x - 5, self->base.position.y},
                        {self->base.position.x, self->base.position.y - 5},
                        {self->base.position.x + 5, self->base.position.y}};
    for(int i = 0; i < 2; ++i){
        line_t line = {vertices[i], vertices[i + 1]};
        graphics->draw_line(graphics, line, chosen_color);

    }
}

    //TODO

void handle_input(input_state_t* self){
    //Read user input based on changes in the position of knobs, buttons etc.
    //Update input state based on user input
    // if (RED_KNOB.is_pressed){
    //     self->quit = true;
    // }
    // if (BLUE_KNOB.is_pressed){
    //     self->pause = true;
    // }
    // if (GREEN_KNOB.is_pressed){
    //     self->fire_bullet = true;
    // }
    // pico vole udelej tu nejak to toceni tema srackama
    
}
    //TODO

void update(game_t* self){
    //Update game state based on player input
    self->player.update(&self->player, &self->input);
    for (int i = 0; i < self->num_player_bullets; i++){
        self->player_bullets[i].update(&self->player_bullets[i], &self->graphics);
    }
    check_target_collisions(self);
    for (int i = 0; i < self->current_level.num_targets; i++){
        if (self->targets[i].health <= 0){
            self->current_level.num_targets--;
            //Remove target from the game
        }
    }
    //Update player properties
    if (self->player.health <= 0){
        //Player dies
        self->input.pause = true;
    }
    if (self->current_level.num_targets == 0){
        //Level is completed
        self->input.pause = true;
    }
}
void game_loop(graphics_object_t* graphics, game_t* game){
    /*
    Main game loop, exit either when the level is completed, the player dies or the game is exited
    Exit states handled by:
    handle_input - exit the game manually
    update - player dies or level is completed
    */
    while(game->input.pause == false && game->input.quit == false){
        //Handle input
        game->input.handle_input(&game->input);
        //Update player based on the input
        game->player.update(&game->player, &game->input);
        //Update game state based on player input
        game->update(game);
        //Clear screen in order to render new game state
        graphics->clear_screen(graphics, chosen_color);
        //Render game state
        game->render(game);
        //Display the rendered game state
        graphics->display(graphics);
    }
    if (game->input.quit == true){
        //Exit the game
        exit(0);
    } else if (game->input.pause == true){
        //Show in-game menu
        ingame_menu.show_menu(&ingame_menu, graphics, fdes, game);
    }
    else{
        //Level is completed or player died
    }
}