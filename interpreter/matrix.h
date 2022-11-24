#ifndef MATRIX_H_
#define MATRIX_H_

#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

namespace my_exceptions {
struct interpreter_error : public std::runtime_error {
    explicit interpreter_error(const std::string &input)
        : std::runtime_error{input} {
    }
};

struct unnknown_command : interpreter_error {
    explicit unnknown_command(const std::string &input)
        : interpreter_error("Unknown command: '" + input + "'\n") {
    }
};

struct invalid_command : interpreter_error {
    explicit invalid_command() : interpreter_error("Invalid command format\n") {
    }
};

struct incorrect_register : interpreter_error {
    explicit incorrect_register(const std::string &input)
        : interpreter_error("'" + input + "' is not a register\n") {
    }
};

struct unopenable_file : interpreter_error {
    explicit unopenable_file(const std::string &file)
        : interpreter_error("Unable to open file '" + file + "'\n") {
    }
};

struct incomplete_data : interpreter_error {
    explicit incomplete_data() : interpreter_error("Invalid file format\n") {
    }
};

struct elem_out_of_bounds : interpreter_error {
    explicit elem_out_of_bounds()
        : interpreter_error("Requested element is out of bounds\n") {
    }
};

struct dimension_mismatch : interpreter_error {
    explicit dimension_mismatch(const std::string &this_m,
                                const std::string &other_m)
        : interpreter_error("Dimension mismatch: lhs=" + this_m +
                            ", rhs=" + other_m + "\n") {
    }
};
}  // namespace my_exceptions

namespace matrix_interpreter {
struct matrix {
private:
    std::vector<std::vector<int>> matrix_m;

public:
    matrix() = default;

    void load(std::string &filename);

    void print();

    void elem(const std::string &raw_row, const std::string &raw_col);

    void add(matrix &other);

    void mul(matrix &other);
};

}  // namespace matrix_interpreter

#endif