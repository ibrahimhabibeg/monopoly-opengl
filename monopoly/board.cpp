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

// There are NUM_CELLS cells on the board
// The cells are numbered from 0 to NUM_CELLS
// Go (bottom right) is cell 0 and numbering moves clockwise
// The last cell (NUM_CELLS-1) is the huge square in the middle of the board
std::tuple<float, float> get_cell_bottom_left(int cell_num)
{
    float x;
    float y;

    if (cell_num < 0 || cell_num >= NUM_CELLS)
    {
        x = -1;
        y = -1;
    }
    else if (cell_num == goCell)
    {
        x = goCellX;
        y = goCellY;
    }
    else if (cell_num < jailCell)
    {
        x = goCellX - BORDER_WIDTH - HR_CELL_WIDTH - ((cell_num - (goCell + 1)) * (HR_CELL_WIDTH + BORDER_WIDTH));
        y = goCellY;
    }
    else if (cell_num == jailCell)
    {
        x = jailCellX;
        y = jailCellY;
    }
    else if (cell_num < freeParkingCell)
    {
        x = jailCellX;
        y = jailCellY + BIG_CELL_HEIGHT + BORDER_WIDTH + ((cell_num - (jailCell + 1)) * (VR_CELL_HEIGHT + BORDER_WIDTH));
    }
    else if (cell_num == freeParkingCell)
    {
        x = freeParkingCellX;
        y = freeParkingCellY;
    }
    else if (cell_num < goToJailCell)
    {
        x = freeParkingCellX + BIG_CELL_WIDTH + BORDER_WIDTH + ((cell_num - (freeParkingCell + 1)) * (HR_CELL_WIDTH + BORDER_WIDTH));
        y = freeParkingCellY;
    }
    else if (cell_num == goToJailCell)
    {
        x = goToJailCellX;
        y = goToJailCellY;
    }
    else if (cell_num < NUM_CELLS - 1)
    {
        x = goToJailCellX;
        y = goToJailCellY - BORDER_WIDTH - VR_CELL_HEIGHT - ((cell_num - (goToJailCell + 1)) * (VR_CELL_HEIGHT + BORDER_WIDTH));
    }
    else
    {
        x = BORDER_WIDTH + BIG_CELL_WIDTH + BORDER_WIDTH;
        y = BORDER_WIDTH + BIG_CELL_HEIGHT + BORDER_WIDTH;
    }
    return std::make_tuple(x, y);
}

std::tuple<float, float> get_colored_bar_bottom_left(int cell_num)
{
    if (cell_num < 0 || cell_num >= NUM_CELLS || cell_num == goCell || cell_num == jailCell || cell_num == freeParkingCell || cell_num == goToJailCell || cell_num == NUM_CELLS - 1)
    {
        return std::make_tuple(-1.0, -1.0);
    }
    float x, y;
    auto t = get_cell_bottom_left(cell_num);
    x = std::get<0>(t);
    y = std::get<1>(t);
    if (cell_num < jailCell)
    {
        return std::make_tuple(x, y + HR_CELL_HEIGHT - HR_CELL_COLORED_BAR_HEIGHT);
    }
    else if (cell_num < freeParkingCell)
    {
        return std::make_tuple(x + VR_CELL_WIDTH - VR_CELL_COLORED_BAR_WIDTH, y);
    }
    else if (cell_num < goToJailCell)
    {
        return std::make_tuple(x, y);
    }
    else
    {
        return std::make_tuple(x, y);
    }
}

void draw_rectangle(float x, float y, float width, float height)
{
    glBegin(GL_POLYGON);
    glVertex3f(x, y, 0.0);
    glVertex3f(x + width, y, 0.0);
    glVertex3f(x + width, y + height, 0.0);
    glVertex3f(x, y + height, 0.0);
    glEnd();
}

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



