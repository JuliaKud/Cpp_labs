#include <iostream>
#include "view.h"

namespace tictactoe {
    void view_compact::print() const {
        std::cout << "\n" << field;
    }
}
