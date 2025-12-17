

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#endif

#include "player.h"
#include "utils.h"
#include "constants.h"

Player::Player(std::tuple<float, float, float> color, float size, double step_duration_ms, float in_cell_x_shift)
    : color(color), size(size), step_duration_ms(step_duration_ms), current_cell(0),
moving(false), in_cell_x_shift(in_cell_x_shift)
{
    auto t = get_cell_center(current_cell);
    x = std::get<0>(t);
    y = std::get<1>(t);
}

void Player::draw()
{
    if(moving){
        updateAnimation(glutGet(GLUT_ELAPSED_TIME));
    }
    float r = std::get<0>(color);
    float g = std::get<1>(color);
    float b = std::get<2>(color);

    glColor3f(r, g, b);
    draw_rectangle(in_cell_x_shift + x - size / 2.0f, y - size / 2.0f, size, size);
}

void Player::startMove(int steps)
{
    if (steps <= 0 || moving)
        return;
    anim_num_steps = steps;
    anim_start_time = glutGet(GLUT_ELAPSED_TIME);
    moving = true;
}

void Player::updateAnimation(double now_ms)
{
    if (!moving)
        return;
    double elapsed = now_ms - anim_start_time;
    int finished_animated_steps = (int) elapsed / step_duration_ms;
    int anim_start_cell = (current_cell + finished_animated_steps) % NUM_PLAYABLE_CELLS;
    int target_cell = (anim_start_cell + 1) % NUM_PLAYABLE_CELLS;
    double move_ratio = (elapsed - finished_animated_steps * step_duration_ms) / step_duration_ms;
    auto anim_start_pos = get_cell_center(anim_start_cell);
    auto target_pos = get_cell_center(target_cell);
    x = (1.0 - move_ratio) * std::get<0>(anim_start_pos) + move_ratio * std::get<0>(target_pos);
    y = (1.0 - move_ratio) * std::get<1>(anim_start_pos) + move_ratio * std::get<1>(target_pos);
  
    if (elapsed >= (step_duration_ms * anim_num_steps))
    {
        current_cell = (current_cell + anim_num_steps) % NUM_PLAYABLE_CELLS;
        auto final_pos = get_cell_center(current_cell);
        x = std::get<0>(final_pos);
        y = std::get<1>(final_pos);
        moving = false;
    }
}

bool Player::isMoving() const
{
    return moving;
}
