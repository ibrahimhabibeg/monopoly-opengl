#define CONSTANTS_H
#include <vector>
using std::vector;

// Sizes
extern const float HR_CELL_WIDTH;
extern const float HR_CELL_HEIGHT;
extern const float VR_CELL_WIDTH;
extern const float VR_CELL_HEIGHT;
extern const float BIG_CELL_HEIGHT;
extern const float BIG_CELL_WIDTH;
extern const float HR_CELL_COLORED_BAR_HEIGHT;
extern const float HR_CELL_COLORED_BAR_WIDTH;
extern const float VR_CELL_COLORED_BAR_HEIGHT;
extern const float VR_CELL_COLORED_BAR_WIDTH;
extern const float BORDER_WIDTH;
extern const int NUM_CELLS_PER_SIDE;
extern const float BOARD_WIDTH;
extern const float BOARD_HEIGHT;
extern const float CENTER_BOX_WIDTH;
extern const float CENTER_BOX_HEIGHT;
extern const int NUM_CELLS;
extern const int NUM_PLAYABLE_CELLS;
extern const int WINDOW_WIDTH;
extern const int WINDOW_HEIGHT;

// Locations
extern const int goCell;
extern const int jailCell;
extern const int freeParkingCell;
extern const int goToJailCell;
extern const float goCellX;
extern const float goCellY;
extern const float jailCellX;
extern const float jailCellY;
extern const float freeParkingCellX;
extern const float freeParkingCellY;
extern const float goToJailCellX;
extern const float goToJailCellY;

// Colors
extern const float CELL_COLOR[3];
extern const float BORDER_COLOR[3];
extern vector<vector<float>> BARS_COLORS;
extern vector<vector<int>> BARS_CELLS;

// Dice constants
extern const float DICE_SIZE;
extern const double DICE_ANIM_DURATION_MS;
extern const int DICE_X_NUMBER_FLIPS;
extern const int DICE_Y_NUMBER_FLIPS;
extern const float DICE_DOT_RADIUS;
extern const int DICE_DOT_NO_OF_SEGMENTS;

// Player constants
extern const float PLAYER_SIZE;
extern const double PLAYER_STEP_DURATION_MS;