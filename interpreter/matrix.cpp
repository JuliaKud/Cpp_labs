#include "matrix.h"

namespace matrix_interpreter {

void matrix::load(std::string &filename) {
    std::ifstream file(filename);

    if (!file.is_open()) {
        throw my_exceptions::unopenable_file(filename);
    }

    int rows = 0;
    int columns = 0;
    if (!(file >> rows >> columns)) {
        throw my_exceptions::incomplete_data();
    }
    if (rows == 0 || columns == 0) {
        rows = 0;
        columns = 0;
    }

    std::vector<std::vector<int>> tmp_matrix(rows, std::vector<int>(columns));

    for (int r = 0; r < rows; ++r) {
        for (int c = 0; c < columns; ++c) {
            if (!(file >> tmp_matrix[r][c])) {
                throw my_exceptions::incomplete_data();
            }
        }
    }
    matrix_m = std::move(tmp_matrix);
}

void matrix::print() {
    for (const auto &row : matrix_m) {
        for (std::size_t col = 0; col < matrix_m[0].size(); ++col) {
            std::cout << row[col];
            if (col != matrix_m[0].size() - 1) {
                std::cout << ' ';
            }
        }
        std::cout << '\n';
    }
}

void matrix::elem(const std::string &raw_row, const std::string &raw_col) {
    for (auto elem : raw_row) {
        if (isdigit(elem) == 0) {
            throw my_exceptions::invalid_command();
        }
    }
    for (auto elem : raw_col) {
        if (isdigit(elem) == 0) {
            throw my_exceptions::invalid_command();
        }
    }

    int row = std::stoi(raw_row);
    int col = std::stoi(raw_col);

    if (row < 0 || row > 1e6 || col < 0 || col > 1e6) {
        throw my_exceptions::invalid_command();
    }
    if (row >= static_cast<int>(matrix_m.size()) ||
        col >= static_cast<int>(matrix_m[0].size())) {
        throw my_exceptions::elem_out_of_bounds();
    }
    std::cout << matrix_m[row][col] << '\n';
}

void matrix::add(matrix &other) {
    if (matrix_m.size() != other.matrix_m.size()) {
        throw my_exceptions::dimension_mismatch(
            std::to_string(matrix_m.size()),
            std::to_string(other.matrix_m.size()));
    }
    if (matrix_m[0].size() != other.matrix_m[0].size()) {
        throw my_exceptions::dimension_mismatch(
            std::to_string(matrix_m[0].size()),
            std::to_string(other.matrix_m[0].size()));
    }

    for (std::size_t r = 0; r < matrix_m.size(); ++r) {
        for (std::size_t c = 0; c < matrix_m[0].size(); ++c) {
            matrix_m[r][c] += other.matrix_m[r][c];
        }
    }
}

void matrix::mul(matrix &other) {
    if (matrix_m[0].size() != other.matrix_m.size()) {
        throw my_exceptions::dimension_mismatch(
            std::to_string(matrix_m[0].size()),
            std::to_string(other.matrix_m.size()));
    }

    std::vector<std::vector<int>> res_matrix(
        matrix_m.size(), std::vector<int>(other.matrix_m[0].size()));
    for (std::size_t r = 0; r < matrix_m.size(); ++r) {
        for (std::size_t c = 0; c < other.matrix_m[0].size(); ++c) {
            for (std::size_t tmp = 0; tmp < matrix_m[0].size(); ++tmp) {
                res_matrix[r][c] += matrix_m[r][tmp] * other.matrix_m[tmp][c];
            }
        }
    }

    matrix_m.clear();
    matrix_m = std::move(res_matrix);
}

}  // namespace matrix_interpreter