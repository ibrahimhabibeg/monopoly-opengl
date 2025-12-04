#include <tuple>
#include <vector>
using std::vector;

#if defined(__APPLE__) && defined(__MACH__)
#include <GLUT/glut.h>
#include <OpenGL/gl.h>
#else
#include <windows.h>
#include <GL/gl.h>
#include <Gl/glut.h>
#endif

#include "constants.h"
#include "utils.h"
#include "board.h"

void draw_board()
{
    glColor3f(BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]);
    draw_rectangle(0.0, 0.0, BOARD_WIDTH, BOARD_HEIGHT);

    for (int i = 0; i < NUM_CELLS; i++)
    {
        float x, y;
        glColor3f(CELL_COLOR[0], CELL_COLOR[1], CELL_COLOR[2]);
        std::tie(x, y) = get_cell_bottom_left(i);
        if (i == NUM_CELLS - 1)
        {
            draw_rectangle(x, y, CENTER_BOX_WIDTH, CENTER_BOX_HEIGHT);
        }
        else if (i == 0 || i == jailCell || i == freeParkingCell || i == goToJailCell)
        {
            draw_rectangle(x, y, BIG_CELL_WIDTH, BIG_CELL_HEIGHT);
        }
        else if (i < jailCell || (i > freeParkingCell && i < goToJailCell))
        {
            draw_rectangle(x, y, HR_CELL_WIDTH, HR_CELL_HEIGHT);
        }
        else
        {
            draw_rectangle(x, y, VR_CELL_WIDTH, VR_CELL_HEIGHT);
        }
    }

    int num_bars_colors = BARS_COLORS.size();
    for (int i = 0; i < num_bars_colors; i++)
    {
        for (int j = 0; j < BARS_CELLS[i].size(); j++)
        {
            float x, y;
            std::tie(x, y) = get_colored_bar_bottom_left(BARS_CELLS[i][j]);
            if (x >= 0 && y >= 0)
            {
                if (BARS_CELLS[i][j] < jailCell)
                {
                    glColor3f(BARS_COLORS[i][0], BARS_COLORS[i][1], BARS_COLORS[i][2]);
                    draw_rectangle(x, y, HR_CELL_COLORED_BAR_WIDTH, HR_CELL_COLORED_BAR_HEIGHT);
                    glColor3f(BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]);
                    draw_rectangle(x, y - BORDER_WIDTH, HR_CELL_COLORED_BAR_WIDTH, BORDER_WIDTH);
                }
                else if (BARS_CELLS[i][j] < freeParkingCell)
                {
                    glColor3f(BARS_COLORS[i][0], BARS_COLORS[i][1], BARS_COLORS[i][2]);
                    draw_rectangle(x, y, VR_CELL_COLORED_BAR_WIDTH, VR_CELL_COLORED_BAR_HEIGHT);
                    glColor3f(BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]);
                    draw_rectangle(x - BORDER_WIDTH, y, BORDER_WIDTH, VR_CELL_COLORED_BAR_HEIGHT);
                }
                else if (BARS_CELLS[i][j] < goToJailCell)
                {
                    glColor3f(BARS_COLORS[i][0], BARS_COLORS[i][1], BARS_COLORS[i][2]);
                    draw_rectangle(x, y, HR_CELL_COLORED_BAR_WIDTH, HR_CELL_COLORED_BAR_HEIGHT);
                    glColor3f(BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]);
                    draw_rectangle(x, y + HR_CELL_COLORED_BAR_HEIGHT, HR_CELL_COLORED_BAR_WIDTH, BORDER_WIDTH);
                }
                else
                {
                    glColor3f(BARS_COLORS[i][0], BARS_COLORS[i][1], BARS_COLORS[i][2]);
                    draw_rectangle(x, y, VR_CELL_COLORED_BAR_WIDTH, VR_CELL_COLORED_BAR_HEIGHT);
                    glColor3f(BORDER_COLOR[0], BORDER_COLOR[1], BORDER_COLOR[2]);
                    draw_rectangle(x + VR_CELL_COLORED_BAR_WIDTH, y, BORDER_WIDTH, VR_CELL_COLORED_BAR_HEIGHT);
                }
            }
        }
    }
}



