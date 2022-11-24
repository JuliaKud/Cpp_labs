#ifndef GAME_H_
#define GAME_H_

namespace tictactoe {
    struct game {
        char current_player;  // NOLINT(misc-non-private-member-variables-in-classes)

        game(const game &) = delete;

        game(game &&) = delete;

        game &operator=(const game &) = delete;

        game &operator=(game &&) = delete;

        ~game() = default;

        void change_player();
    };

}
#endif