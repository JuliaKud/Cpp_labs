#include <iostream>
#include <utility>

#ifndef UNIQUE_PTR_
#define UNIQUE_PTR_

namespace ptrs::unique {

template <typename T>
struct default_Deleter {
    void operator()(T *ptr) {
        delete ptr;
    }
};

template <typename T, typename Deleter = default_Deleter<T>>
struct unique_ptr {
private:
    T *ptr = nullptr;
    Deleter del;

public:
    unique_ptr() = default;

    // cppcheck-suppress noExplicitConstructor
    unique_ptr(std::nullptr_t){};

    unique_ptr(const unique_ptr &other) = delete;

    unique_ptr &operator=(const unique_ptr &other) = delete;

    unique_ptr(unique_ptr &&other)
        : ptr(std::exchange(other.ptr, nullptr)), del(std::move(other.del)) {
    }

    unique_ptr &operator=(unique_ptr &&other) {
        reset(other.release());
        del = std::move(other.del);
        return *this;
    }

    unique_ptr &operator=(std::nullptr_t) {
        reset();
        return *this;
    }

    explicit unique_ptr(T *other) : ptr(std::move(other)) {
    }
    explicit unique_ptr(T *other, Deleter other_del)
        : ptr(std::move(other)), del(std::move(other_del)) {
    }

    ~unique_ptr() {
        if (ptr != nullptr) {
            del(ptr);
        }
    }

    T *get() const {
        return ptr;
    }

    [[nodiscard]] T *release() {
        return std::exchange(ptr, nullptr);
    }

    explicit operator bool() const {
        return static_cast<bool>(ptr);
    }

    [[nodiscard]] T &operator*() const {
        return *ptr;
    }

    [[nodiscard]] T *operator->() const {
        return &(this->operator*());
    }

    friend bool operator==(const unique_ptr &obj1, const unique_ptr &obj2) {
        return obj1.ptr == obj2.ptr;
    }

    friend bool operator!=(const unique_ptr &obj1, const unique_ptr &obj2) {
        return obj1.ptr != obj2.ptr;
    }

    friend void swap(unique_ptr<T, Deleter> &obj1,
                     unique_ptr<T, Deleter> &obj2) {
        if (obj1.ptr != obj2.ptr) {
            std::swap(obj1.ptr, obj2.ptr);
            std::swap(obj1.del, obj2.del);
        }
    }

    void reset() {
        if (ptr != nullptr) {
            del(ptr);
        }
        ptr = nullptr;
    }

    void reset(T *obj) {
        if (ptr != nullptr) {
            del(ptr);
        }
        ptr = std::move(obj);
    }
};
}  // namespace ptrs::unique
#endif
