#define UTILS_H
#include <tuple>

std::tuple<float, float> get_cell_bottom_left(int cell_num);
std::tuple<float, float> get_cell_center(int cell_num);
std::tuple<float, float> get_colored_bar_bottom_left(int cell_num);
void draw_rectangle(float x, float y, float width, float height);
