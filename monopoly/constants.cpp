#include "constants.h"

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
const int NUM_PLAYABLE_CELLS = NUM_CELLS - 1;
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

// Dice constants
const float DICE_SIZE = 2.0f;
const double DICE_ANIM_DURATION_MS = 1000.0;
const int DICE_X_NUMBER_FLIPS = 1;
const int DICE_Y_NUMBER_FLIPS = 2;
const float DICE_DOT_RADIUS = 0.1f * DICE_SIZE;
const int DICE_DOT_NO_OF_SEGMENTS = 50;

// Player constants
const float PLAYER_SIZE = 1.0f;
const double PLAYER_STEP_DURATION_MS = 300.0;