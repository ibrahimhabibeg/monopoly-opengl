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

// Sizes
const float HR_CELL_WIDTH = 3.0;
const float HR_CELL_HEIGHT = 5.0;
const float VR_CELL_WIDTH = HR_CELL_HEIGHT;
const float VR_CELL_HEIGHT = HR_CELL_WIDTH;
const float BIG_CELL_HEIGHT = HR_CELL_HEIGHT;
const float BIG_CELL_WIDTH = VR_CELL_WIDTH;
const float HR_CELL_COLORED_BAR_HEIGHT = 1.0;
const float HR_CELL_COLORED_BAR_WIDTH = HR_CELL_WIDTH;
const float VR_CELL_COLORED_BAR_HEIGHT = VR_CELL_HEIGHT;
const float VR_CELL_COLORED_BAR_WIDTH = HR_CELL_COLORED_BAR_HEIGHT;
const float BORDER_WIDTH = 0.2;
const int NUM_CELLS_PER_SIDE = 9;
const float BOARD_WIDTH = (2 * BIG_CELL_WIDTH) + (NUM_CELLS_PER_SIDE * HR_CELL_WIDTH) + ((2 + NUM_CELLS_PER_SIDE + 1) * BORDER_WIDTH);
const float BOARD_HEIGHT = (2 * BIG_CELL_HEIGHT) + (NUM_CELLS_PER_SIDE * VR_CELL_HEIGHT) + ((2 + NUM_CELLS_PER_SIDE + 1) * BORDER_WIDTH);
const float CENTER_BOX_WIDTH = BOARD_WIDTH - 4 * BORDER_WIDTH - 2 * BIG_CELL_WIDTH;
const float CENTER_BOX_HEIGHT = BOARD_HEIGHT - 4 * BORDER_WIDTH - 2 * BIG_CELL_HEIGHT;
const int NUM_CELLS = 4 + 4 * NUM_CELLS_PER_SIDE + 1;
const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = (WINDOW_WIDTH * BOARD_HEIGHT) / BOARD_WIDTH;

// Locations
const int goCell = 0;
const int jailCell = 1 + NUM_CELLS_PER_SIDE;
const int freeParkingCell = 2 + 2 * NUM_CELLS_PER_SIDE;
const int goToJailCell = 3 + 3 * NUM_CELLS_PER_SIDE;
const float goCellX = BOARD_WIDTH - BORDER_WIDTH - BIG_CELL_WIDTH;
const float goCellY = BORDER_WIDTH;
const float jailCellX = BORDER_WIDTH;
const float jailCellY = BORDER_WIDTH;
const float freeParkingCellX = BORDER_WIDTH;
const float freeParkingCellY = BOARD_HEIGHT - BORDER_WIDTH - BIG_CELL_HEIGHT;
const float goToJailCellX = BOARD_WIDTH - BORDER_WIDTH - BIG_CELL_WIDTH;
const float goToJailCellY = BOARD_HEIGHT - BORDER_WIDTH - BIG_CELL_HEIGHT;

// Colors
const float CELL_COLOR[3] = {0.816, 0.899, 0.82};
const float BORDER_COLOR[3] = {0.0, 0.0, 0.0};
vector<vector<float>> BARS_COLORS = {
    {150.0 / 255.0, 80.0 / 255.0, 58.0 / 255.0},
    {168.0 / 255.0, 225.0 / 255.0, 247.0 / 255.0},
    {218.0 / 255.0, 58.0 / 255.0, 149.0 / 255.0},
    {246.0 / 255.0, 145.0 / 255.0, 49.0 / 255.0},
    {235.0 / 255.0, 20.0 / 255.0, 36.0 / 255.0},
    {255.0 / 255.0, 239.0 / 255.0, 57.0 / 255.0},
    {64.0 / 255.0, 173.0 / 255.0, 94.0 / 255.0},
    {0.0 / 255.0, 117.0 / 255.0, 185.0 / 255.0},
};
vector<vector<int>> BARS_CELLS = {
    {1, 3},
    {6, 8, 9},
    {11, 13, 14},
    {16, 18, 19},
    {21, 23, 24},
    {26, 27, 29},
    {31, 32, 34},
    {37, 39},
};

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
    if (cell_num < jailCell )
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

void draw(void)
{
    glClear(GL_COLOR_BUFFER_BIT);
    draw_board();
    glFlush();
}

void init()
{
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0, BOARD_WIDTH, 0.0, BOARD_HEIGHT, -1.0, 1.0);
}
int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowSize(WINDOW_WIDTH, WINDOW_HEIGHT);
    glutInitWindowPosition(100, 100);
    glutCreateWindow("Monopoly Board");
    init();
    glutDisplayFunc(draw);
    glutMainLoop();
    return 0;
}
