#include <iostream>
#include <sstream>
#include "game.h"
#include "view.h"

int main() {
    tictactoe::game state{'O'};
    tictactoe::view_compact field{
        "..........\n..........\n.........."
        "\n..........\n..........\n.........."
        "\n..........\n..........\n.........."
        "\n..........\n"};
    std::string raw_x;
    std::string raw_y;

    field.print();
    std::cout << state.current_player << " move: ";

    std::stringstream ss;
    std::string line;
    std::getline(std::cin, line);
    ss << line;

    while (!line.empty()) {
        ss >> raw_x >> raw_y;
        int coord_x = std::stoi(raw_x);
        int coord_y = std::stoi(raw_y);

        if (coord_x == -1 && coord_y == -1) {
            break;
        }
        if (field.field[11 * coord_x + coord_y] != '.') {
            std::cout << "Bad move!\n";
        } else {
            field.field[11 * coord_x + coord_y] = state.current_player;
            state.change_player();
            field.print();
        }

        std::cout << state.current_player << " move: ";
        ss.clear();
        std::getline(std::cin, line);
        ss << line;
    }
}
