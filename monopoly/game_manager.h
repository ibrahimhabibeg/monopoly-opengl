#define GAME_MANAGER_H
#include "dice.h"
#include "player.h"
#include <vector>
class GameManager {
public:
    GameManager();
    void draw();
    void rollDice();
private:
    Dice dice1;
    Dice dice2;
    std::vector<Player> players;
    int current_player_index;
    bool awaiting_dice_finish_animation;
    bool awaiting_player_finish_animation;
};
