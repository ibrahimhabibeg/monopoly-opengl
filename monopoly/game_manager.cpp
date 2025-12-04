#include "game_manager.h"
#include "constants.h"
#include "board.h"

GameManager::GameManager()
    : dice1(BOARD_WIDTH / 2 - DICE_SIZE - 0.5f,
            BOARD_HEIGHT / 2 - DICE_SIZE / 2,
            DICE_SIZE,
            DICE_ANIM_DURATION_MS),
      dice2(BOARD_WIDTH / 2 + 0.5f,
            BOARD_HEIGHT / 2 - DICE_SIZE / 2,
            DICE_SIZE,
            DICE_ANIM_DURATION_MS),
        awaiting_dice_finish_animation(false),
        awaiting_player_finish_animation(false),
        current_player_index(0)
{
    players.push_back(Player(std::make_tuple(1.0f, 0.0f, 0.0f), PLAYER_SIZE, PLAYER_STEP_DURATION_MS));
    players.push_back(Player(std::make_tuple(0.0f, 0.0f, 1.0f), PLAYER_SIZE, PLAYER_STEP_DURATION_MS));
}

void GameManager::draw()
{
    if(!dice1.isRolling() && !dice2.isRolling() && awaiting_dice_finish_animation){
        players[current_player_index].startMove(dice1.getValue() + dice2.getValue());
        awaiting_dice_finish_animation = false;
        awaiting_player_finish_animation = true;
    }
    if(!players[current_player_index].isMoving() && awaiting_player_finish_animation){
        awaiting_player_finish_animation = false;
        current_player_index = (current_player_index + 1) % players.size();
    }
    draw_board();
    dice1.draw();
    dice2.draw();
    for(auto& player : players){
        player.draw();
    }
}

void GameManager::rollDice()
{
    if(awaiting_dice_finish_animation || awaiting_player_finish_animation)
        return;
    dice1.roll();
    dice2.roll();
    awaiting_dice_finish_animation = true;
}
