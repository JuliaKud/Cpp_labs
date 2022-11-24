#ifndef VIEW_H_
#define VIEW_H_

#include <string>

namespace tictactoe {
    struct view_compact {
        std::string field;  // NOLINT(misc-non-private-member-variables-in-classes)

        view_compact(const view_compact &) = delete;

        view_compact(view_compact &&) = delete;

        view_compact &operator=(const view_compact &) = delete;

        view_compact &operator=(view_compact &&) = delete;

        void print() const;

        ~view_compact() = default;
    };
}

#endif