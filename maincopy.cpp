#include "include\block.h"
#include "include\grid.h"
#include "include\game.h"
#include "blockcopy.cpp"
#include <iostream>

#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <stdarg.h>
#include <sys/stat.h>
#include <errno.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <stdint.h>

using namespace std;
double last_update_time = 0.0;

bool event_triggered(double interval)
{
    double current_time = GetTime();

    if(current_time - last_update_time >= interval) {
        last_update_time = current_time;
        return true;
    }
    return false;
}

void draw_intro_1(Font font)
{
    // DrawText("TETRIS", 140, 20, 65, 2, WHITE);
    DrawTextEx(font, "T", {140 - 6, 275}, 80, 1, RED);
    DrawTextEx(font, "E", {185 - 6, 275}, 80, 1, GREEN);
    DrawTextEx(font, "T", {230 - 6, 275}, 80, 1, YELLOW);
    DrawTextEx(font, "R", {280 - 6, 275}, 80, 1, PURPLE);
    DrawTextEx(font, "I", {325 - 6, 275}, 80, 1, ORANGE);
    DrawTextEx(font, "S", {375 - 6, 275}, 80, 1, BLUE);
}

void draw_logo(Font font)
{
    // DrawText("TETRIS", 140, 20, 65,52, .1WHITE);
    DrawTextEx(font, "T", {345 + 2, 27}, 55, 2.1, RED);
    DrawTextEx(font, "E", {370 + 2, 27}, 55, 2.1, GREEN);
    DrawTextEx(font, "T", {395 + 2, 27}, 55, 2.1, YELLOW);
    DrawTextEx(font, "R", {420 + 2, 27}, 55, 2.1, PURPLE);
    DrawTextEx(font, "I", {445 + 2, 27}, 55, 2.1, ORANGE);
    DrawTextEx(font, "S", {470 + 2, 27}, 55, 2.1, BLUE);;
}

// Main function to setup and run the game
int main(int ac, char **av)
{
    std::cout << "Hello World" << std::endl;
    InitWindow(530, 620, "TETRIS");
    SetTargetFPS(60);

    double time_limit = 7.0;
    double time_start = GetTime();
    int fc = 0;

    Font font = LoadFontEx("monogram.ttf", 64, 0, 0);
    Texture2D arrows = LoadTexture("arrows1.png");

    Game game = Game();

    game.game_score = 0;
    Vector2 text_size = MeasureTextEx(font, TextFormat(" %i", game.game_score), 45, 2);
        // Calcule la nouvelle position pour centrer
    float text_x = 390 - text_size.x / 2; // Centrage horizontal
    float text_y = 147; // Position verticale fixe

    while(WindowShouldClose() == false)
    {
        double elapsed_time = GetTime() - time_start;
        BeginDrawing();
        game.handle_input();
        if (elapsed_time < time_limit && !game.start && !game.skip) {
                if (elapsed_time < 3.5)
                    DrawTextEx(font, "Pococo Studios Presents", {65, 290}, 34, 2, WHITE);
                else
                    draw_intro_1(font);
                ClearBackground(Color(BLACK));
        }
        else {
            if (event_triggered(0.4) && !game.pause && game.start)
                game.move_block_down();
            ClearBackground(Color{84, 44, 155, 255});
            draw_logo(font);
            DrawTextEx(font, "Score", {378, 90}, 35, 2, WHITE);
            DrawRectangleRounded({340, 140, 170, 60}, 0.3, 6, Color{59, 85, 162, 255});
            DrawTextEx(font, "Next Block", {345, 230}, 30, 2, WHITE);
            DrawRectangleRounded({340, 270, 170, 170}, 0.3, 6, Color{59, 85, 162, 255});
            game.draw();
            DrawTextEx(font, TextFormat(" %i", game.game_score), (Vector2){text_x, text_y}, 45, 2, WHITE);
            if (game.game_o)
                DrawTextEx(font, "GAME OVER :(", {70, 130}, 50, 2, WHITE);
            if (game.pause)
                DrawTextEx(font, "PAUSE", {95, 290}, 50, 2, WHITE);
            if (!game.start) {
                fc++;
                if (((fc/30)%2)) {
                    DrawTextEx(font, "Tap ENTER", {355, 450}, 30, 2, WHITE);
                    DrawTextEx(font, "to start", {360, 475}, 30, 2, WHITE);
                }
            }
            DrawTexture(arrows, 320, 550, WHITE);
            if (game.game_score == 100)
                DrawTextEx(font, TextFormat("Score : %i !!!", game.game_score), {325, 290}, 30, 2, WHITE);
        }
        EndDrawing();
    }
    CloseWindow();
    return 0;
}
