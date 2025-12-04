#define PLAYER_H
#include <tuple>
class Player {
public:
    Player(std::tuple<float, float, float> color, float size, double step_duration_ms);
    void draw();
    void startMove(int steps);
    void updateAnimation(double now_ms);
    bool isMoving() const;
private:
    std::tuple<float, float, float> color;
    float size;
    double step_duration_ms;
    float x, y;
    int current_cell;
    double anim_start_time;
    int anim_num_steps;
    bool moving;
};
