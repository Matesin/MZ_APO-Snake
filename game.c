#include "game.h"

color_t chosen_color = {255, 255, 255}; //update this value throughout the game

void update_player_ship(player_ship_t* self, graphics_object_t* graphics){
    //Update player position based on user input
    //Update player properties (health etc.)
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
void handle_input(input_state_t* self){
    //Read user input based on changes in the position of knobs, buttons etc.
    //Update input state based on user input
}
void game_loop(graphics_object_t* graphics, player_ship_t* player, game_t* game){
    while(true){
        //Handle input
        game->input.handle_input(&game->input);
        //Update player based on the input
        game->player.update(&game->player, graphics);
        //Update game state based on player input
        game->update(game);
        //Clear screen in order to render new game state
        graphics->clear_screen(graphics, chosen_color);
        //Render game state
        game->render(game);
        //Display the rendered game state
        graphics->display(graphics);
    }
}