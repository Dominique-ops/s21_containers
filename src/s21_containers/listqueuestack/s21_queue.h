#ifndef CONTAINERS_SRC_QUEUE_H_
#define CONTAINERS_SRC_QUEUE_H_

#include <algorithm>

#include "s21_list.h"

namespace s21 {
template <typename T, class Container = s21::list<T>>
class queue {
  using value_type = T;
  using size_type = size_t;
  using reference = T&;
  using const_reference = const T&;

 public:
  queue() : element_() {}
  explicit queue(std::initializer_list<value_type> const& other)
      : element_(other){};
  queue(const queue& other) : element_(other.element_){};
  queue(queue&& other) : element_(std::move(other.element_)){};
  ~queue() {}

  queue& operator=(const queue& other) {
    *this = other;
    return *this;
  }

  queue& operator=(queue&& other) {
    element_ = std::move(other.element_);
    std::swap(element_);
    return *this;
  }

  reference front() { return element_.front(); }
  const_reference front() const { return element_.front(); }
  reference back() { return element_.back(); }
  const_reference back() const { return element_.back(); }

  bool empty() const { return element_.empty(); }
  size_type size() const { return element_.size(); }

  void push(const T& value) { element_.push_back(value); }
  void push(T&& value) { element_.push_back(std::move(value)); }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    element_.insert_many_back(std::forward<Args>(args)...);
  }

  void pop() { element_.pop_front(); }
  void swap(queue& other) { std::swap(element_, other.element_); }

  template <typename T1, typename T2>
  bool operator==(queue<T2>& rhs) {
    return equal(rhs);
  }

 private:
  Container element_;
};
}  // namespace s21

#endif