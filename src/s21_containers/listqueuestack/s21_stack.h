#ifndef CONSTAINERS_SRC_S21_STACK_H_
#define CONSTAINERS_SRC_S21_STACK_H_
#include <memory>

namespace s21 {

template <class T>
class stack {
 public:
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = size_t;
  struct node {
    value_type value_;
    node* next_;
    node* prev_;
    node() : value_(), next_(nullptr), prev_(nullptr){};
    node(value_type value) : value_(value), next_(nullptr), prev_(nullptr){};
  };

 public:
  stack() : str_(nullptr), end_(nullptr), size_(0U){};
  stack(std::initializer_list<value_type> const& items) : stack() {
    for (auto it = items.begin(); it != items.end(); it++) {
      push(*it);
    }
  }
  stack(const stack& s) : stack() {
    for (size_type i = 0; i < s.size(); ++i) {
      push(s[i]->value_);
    }
  }

  node* operator[](const size_type index) const {
    if (!str_) return nullptr;
    node* p = str_;
    for (size_type i = 0; i < index; i++) {
      p = p->next_;
      if (!p) return nullptr;
    }
    return p;
  }
  stack(stack&& s) noexcept : stack() {
    swap(s);
    s.clear();
  }
  ~stack() { this->clear(); }
  stack& operator=(stack&& s) {
    swap(s);
    s.clear();
    return *this;
  }

  const_reference top() const { return end_->value_; }

  bool empty() const noexcept { return str_ == nullptr; }

  size_type size() const noexcept { return size_; }

  void push(const_reference val) {
    std::unique_ptr<node> buff(new node(val));
    if (empty()) {
      str_ = end_ = buff.get();
    } else {
      buff->prev_ = end_;
      end_->next_ = buff.get();
      end_ = buff.get();
    }
    buff.release();
    size_++;
  }
  void pop() {
    if (empty()) return;
    std::unique_ptr<node> buff(end_);
    if (end_->prev_ == nullptr) {
      end_ = str_ = nullptr;
    } else {
      end_->prev_->next_ = nullptr;
      end_ = end_->prev_;
    }
    size_--;
  }

  void swap(stack& other) {
    std::swap(other.str_, str_);
    std::swap(other.end_, end_);
    std::swap(other.size_, size_);
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    value_type temp_(std::forward<Args>(args)...);
    push(temp_);
  }

 private:
  node* str_;
  node* end_;
  size_type size_;
  void clear() {
    size_ = 0U;
    node* element_ = str_;
    while (element_) {
      node* next = element_->next_;
      delete element_;
      element_ = next;
    }
  }
};
}  // namespace s21

#endif