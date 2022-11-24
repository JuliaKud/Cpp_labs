#include <iostream>
#include <utility>

#ifndef SHARED_PTR_
#define SHARED_PTR_

namespace ptrs::shared {
template <typename T>
struct shared_ptr {
private:
    T *ptr = nullptr;
    int *count = nullptr;

    void check() {
        if (ptr) {
            (*count)--;
            if (*count <= 0) {
                delete ptr;
                delete count;
            }
        }
    }

public:
    shared_ptr() = default;

    // cppcheck-suppress noExplicitConstructor
    shared_ptr(std::nullptr_t) {
    }

    shared_ptr &operator=(std::nullptr_t) {
        reset();
        return *this;
    }

    // cppcheck-suppress copyCtorPointerCopying
    shared_ptr(const shared_ptr &other) : ptr(other.ptr), count(other.count) {
        if (ptr) {
            (*count)++;
        }
    }

    shared_ptr &operator=(const shared_ptr &other) {
        if (other.ptr != ptr) {
            check();
            ptr = other.ptr;
            count = other.count;
            if (ptr) {
                (*count)++;
            }
        }
        if (ptr == nullptr && other.ptr == nullptr) {
            count = other.count;
        }
        return *this;
    }

    shared_ptr(shared_ptr &&other)
        : ptr(std::exchange(other.ptr, nullptr)),
          count(std::exchange(other.count, nullptr)) {
    }

    shared_ptr &operator=(shared_ptr &&other) {
        if (other.ptr != ptr) {
            check();
            ptr = std::exchange(other.ptr, nullptr);
            count = std::exchange(other.count, nullptr);
        }
        return *this;
    }

    explicit shared_ptr(T *other) : ptr(std::move(other)) {
        if (other) {
            count = new int(1);
        }
    }

    ~shared_ptr() {
        check();
    }

    [[nodiscard]] T &operator*() const {
        return *ptr;
    }

    [[nodiscard]] T *operator->() const {
        return &(this->operator*());
    }

    T *get() const {
        return ptr;
    }

    explicit operator bool() const {
        return static_cast<bool>(ptr);
    }

    friend bool operator==(const shared_ptr &obj1, const shared_ptr &obj2) {
        return obj1.ptr == obj2.ptr;
    }

    friend bool operator!=(const shared_ptr &obj1, const shared_ptr &obj2) {
        return obj1.ptr != obj2.ptr;
    }

    friend void swap(shared_ptr<T> &obj1, shared_ptr<T> &obj2) {
        if (obj1.ptr != obj2.ptr) {
            std::swap(obj1.ptr, obj2.ptr);
            std::swap(obj1.count, obj2.count);
        }
    }

    void reset() {
        check();
        ptr = nullptr;
        count = nullptr;
    }

    void reset(T *obj) {
        reset();
        if (obj) {
            count = new int(1);
        } else {
            count = nullptr;
        }
        ptr = obj;
    }
};
}  // namespace ptrs::shared

#endif
