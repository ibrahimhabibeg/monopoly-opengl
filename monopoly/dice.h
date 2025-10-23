#define DICE_H

class Dice
{
public:
    Dice(float end_x, float end_y, float size, double anim_duration_ms);
    void roll();
    void draw();
    int getValue() const;
    bool isRolling() const;
private:
    void drawCube();
    void updateAnimation(double now_ms);
    void reset();
    float start_x, start_y, end_x, end_y, size;
    double anim_duration_ms;
    double roll_start_time;
    float x, y;
    float angle_x, angle_y;
    int value;
    bool rolling;
};
