#include "game.h"

namespace tictactoe {
    void game::change_player() {
        if (current_player == 'O') {
            current_player = 'X';
        } else {
            current_player = 'O';
        }
    }
}