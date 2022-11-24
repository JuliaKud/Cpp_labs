#include <set>
#include "matrix.h"

int correct_reg(std::stringstream &parsed_input) {
    std::string raw_reg;
    if (!(parsed_input >> raw_reg)) {
        throw my_exceptions::invalid_command();
    }

    if (raw_reg.size() != 2 || raw_reg[0] != '$' || isdigit(raw_reg[1]) == 0) {
        throw my_exceptions::incorrect_register(raw_reg);
    }

    return raw_reg[1] - '0';
}

void extra_arguments(std::stringstream &parsed_input) {
    std::string extra_args;
    if (parsed_input >> extra_args) {
        throw my_exceptions::invalid_command();
    }
}

int main() {  // NOLINT(bugprone-exception-escape)
    static std::set<std::string> correct_cmd{"load", "print", "elem",
                                             "exit", "add",   "mul"};
    std::vector<matrix_interpreter::matrix> registers(10);

    std::string input;

    while (std::getline(std::cin, input)) {
        std::stringstream parsed_input;
        parsed_input << input;
        try {
            std::string cmd;
            if (!(parsed_input >> cmd)) {
                throw my_exceptions::invalid_command();
            }
            if (correct_cmd.count(cmd) == 0) {
                throw my_exceptions::unnknown_command(cmd);
            }

            if (cmd == "exit") {
                extra_arguments(parsed_input);
                break;
            }

            int reg = correct_reg(parsed_input);

            if (cmd == "load") {
                std::string filename;
                if (!(parsed_input >> filename)) {
                    throw my_exceptions::invalid_command();
                }
                extra_arguments(parsed_input);
                registers[reg].load(filename);

            } else if (cmd == "print") {
                extra_arguments(parsed_input);
                registers[reg].print();

            } else if (cmd == "elem") {
                std::string row;
                std::string col;
                if (!(parsed_input >> row >> col)) {
                    throw my_exceptions::invalid_command();
                }
                extra_arguments(parsed_input);
                registers[reg].elem(row, col);
            } else if (cmd == "add") {
                int other_reg = correct_reg(parsed_input);
                extra_arguments(parsed_input);
                registers[reg].add(registers[other_reg]);
            } else if (cmd == "mul") {
                int other_reg = correct_reg(parsed_input);
                extra_arguments(parsed_input);
                registers[reg].mul(registers[other_reg]);
            }
        } catch (my_exceptions::interpreter_error &err) {
            std::cout << err.what();
        }
    }
}