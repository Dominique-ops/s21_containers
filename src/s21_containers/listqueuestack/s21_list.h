#ifndef CONTAINERS_SRC_S21_LIST_H_
#define CONTAINERS_SRC_S21_LIST_H_

#include <cmath>
#include <limits>
#include <memory>

namespace s21 {
template <typename T>
class list {
  using value_type = T;
  using reference = T&;
  using const_reference = const T&;
  using size_type = std::size_t;
  struct Node;

 public:
  template <typename value_type>
  class listIterator {
   public:
    friend class list<T>;
    listIterator() { element_ = nullptr; }
    listIterator(Node* ptr) : element_(ptr){};

    reference operator*() const { return element_->value_; }

    value_type* operator->() const { return &(element_->value_); }

    listIterator& operator++() {
      element_ = element_->next_;
      return *this;
    }

    listIterator operator++(int) {
      listIterator tmp(*this);
      ++(*this);
      return tmp;
    }

    listIterator& operator--() {
      element_ = element_->prev_;
      return *this;
    }

    listIterator operator--(int) {
      listIterator tmp(*this);
      --(*this);
      return tmp;
    }

    bool operator==(const listIterator& other) const {
      return element_ == other.element_;
    }

    bool operator!=(const listIterator& other) const {
      return element_ != other.element_;
    }

   private:
    friend class list<T>;  // can use private of list
    Node* element_;
  };

  template <typename value_type>
  class listConstIterator : public listIterator<T> {
   public:
    listConstIterator();
    listConstIterator(listIterator<T> other) : listIterator<T>(other) {}

    const_reference operator*() const { return listIterator<T>::operator*(); }
  };
  using iterator = listIterator<T>;
  using const_iterator = listConstIterator<T>;

  list() {}

  list(size_type n) {
    for (size_type i = 0; i < n; i++) {
      push_back(value_type());
    }
  }

  list(std::initializer_list<value_type> const& items) {
    for (const auto& item : items) {
      push_back(item);
    }
  }

  list(const list& l) { operator=(l); }

  list(list&& l) { swap(l); }

  ~list() { clear(); }

  list& operator=(const list& l) {
    copy(l);
    return *this;
  }

  list& operator=(list&& l) {
    if (this != &l) {
      clear();
      swap(l);
    }
    return *this;
  }

  reference front() { return str_->value_; }
  const_reference front() const { return str_->value_; }
  reference back() { return end_->value_; }
  const_reference back() const { return end_->value_; }

  iterator begin() noexcept { return iterator(str_); }
  iterator end() noexcept { return iterator(nullptr); }

  const_iterator cbegin() const { return const_iterator(str_); }
  const_iterator cend() const { return const_iterator(end_); }

  bool empty() const { return size_ == 0; }

  size_type size() const { return size_; }

  size_type max_size() const {
    return std::numeric_limits<size_type>::max() / sizeof(Node);
  }

  void clear() {
    Node* nodeptr = str_;
    while (nodeptr != nullptr) {
      Node* nextptr = nodeptr->next_;
      delete nodeptr;
      nodeptr = nextptr;
    }
    size_ = 0;
    str_ = nullptr;
    end_ = nullptr;
  }

  iterator insert(iterator pos, const_reference value) {
    Node* new_node = new Node(value);
    if (empty()) {
      str_ = new_node;
      end_ = new_node;
    } else {
      if (pos == begin()) {
        new_node->next_ = str_;
        str_->prev_ = new_node;
        str_ = new_node;
      } else if (pos == end()) {
        end_->next_ = new_node;
        new_node->prev_ = end_;
        end_ = new_node;
      } else {
        Node* element_ = pos.element_;
        new_node->prev_ = element_->prev_;
        new_node->next_ = element_;
        element_->prev_->next_ = new_node;
        element_->prev_ = new_node;
      }
    }
    size_++;
    return iterator(new_node);
  }

  iterator erase(iterator pos) {
    if (empty()) {
      return end();
    }
    if (pos == begin()) {
      str_ = str_->next_;
      if (str_ != nullptr) {
        str_->prev_ = nullptr;
      } else {
        end_ = nullptr;
      }
    } else {
      Node* prev_node = pos.element_->prev_;
      Node* next_node = pos.element_->next_;
      prev_node->next_ = next_node;
      if (next_node != nullptr) {
        next_node->prev_ = prev_node;
      } else {
        end_ = prev_node;
      }
    }
    delete pos.element_;
    size_--;
    return iterator(pos.element_);
  }

  void push_back(const_reference value) { insert(end(), value); }

  void pop_back() {
    Node* temp = end_->prev_;
    delete end_;
    end_ = temp;
    if (end_) {
      end_->next_ = nullptr;
    } else {
      str_ = nullptr;
    }
    if (size_ > 0) {
      --size_;
    }
  }

  void push_front(const_reference value) { insert(begin(), value); }

  void pop_front() {
    if (!(empty())) {
      erase(begin());
    }
  }

  void swap(list& other) {
    std::swap(str_, other.str_);
    std::swap(end_, other.end_);
    std::swap(size_, other.size_);
  }

  void merge(list& other) {
    if (size_ + other.size_ > max_size()) throw "Maximum of container";
    if ((this != &other) && (!(other.empty()))) {
      if (empty()) {
        copy(other);
      } else {
        iterator This = begin();
        iterator Other = other.begin();
        while (Other != other.end()) {
          if (This != end()) {
            if (This.element_->value_ >= Other.element_->value_) {
              insert(This, Other.element_->value_);
              ++Other;
            } else {
              ++This;
            }
          } else {
            insert(This, Other.element_->value_);
            ++Other;
          }
        }
      }
      other.clear();
    }
  }

  void splice(const_iterator pos, list& other) {
    if (!other.empty()) {
      if (pos == end()) {
        end_->next_ = other.str_;
        other.str_->prev_ = end_;
        end_ = other.end_;
        other.str_ = nullptr;
        other.end_ = nullptr;
      } else {
        Node* prev_node = pos.element_->prev_;
        prev_node->next_ = other.str_;
        other.str_->prev_ = prev_node;
        end_->next_ = other.end_;
        other.end_->prev_ = end_;
        end_ = other.end_;
        other.str_ = nullptr;
        other.end_ = nullptr;
      }
      size_ += other.size_;
      other.size_ = 0;
    }
  }

  void reverse() {
    if ((!empty()) && (size_ > 1)) {
      Node* temp = nullptr;
      for (auto it = begin(); it != end(); it = temp) {
        temp = it.element_->next_;
        it.element_->next_ = it.element_->prev_;
        it.element_->prev_ = temp;
      }
      temp = str_;
      str_ = end_;
      end_ = temp;
    }
  }

  void unique() {
    if (size_ > 1) {
      Node* element_ = str_;
      while (element_->next_ != nullptr) {
        if (element_->value_ == element_->next_->value_) {
          Node* dup = element_->next_;
          element_->next_ = dup->next_;
          if (dup->next_ != nullptr) {
            dup->next_->prev_ = element_;
          }
          delete dup;
          size_--;
        } else {
          element_ = element_->next_;
        }
      }
    }
  }

  void sort() {
    if (size_ > 1) {
      for (auto it = begin(); it != end(); it++) {
        for (auto jt = it; jt != end(); jt++) {
          if (it.element_->value_ > jt.element_->value_) {
            std::swap(it.element_->value_, jt.element_->value_);
          }
        }
      }
    }
  }

  void copy(const list& l) {
    if (this != &l) {
      clear();
      Node* element_ = l.str_;
      for (size_type i = 0; i != l.size_; i++) {
        push_back(element_->value_);
        element_ = element_->next_;
      }
    }
  }

  template <class... Args>
  iterator insert_many(const_iterator pos, Args&&... args)

  {
    for (const auto& arg : {args...}) {
      insert(pos, arg);
    }
    return pos;
  }

  template <class... Args>
  void insert_many_back(Args&&... args) {
    for (const auto& arg : {args...}) {
      push_back(arg);
    }
  }

  template <class... Args>
  void insert_many_front(Args&&... args) {
    auto it = begin();
    for (const auto& arg : {args...}) {
      insert(it, arg);
    }
  }

 private:
  struct Node {
    value_type value_;
    Node* prev_ = nullptr;
    Node* next_ = nullptr;
    explicit Node(const value_type& value, Node* prev = nullptr,
                  Node* next_ = nullptr)
        : value_(value), prev_(prev), next_(next_) {}
  };

  Node* str_ = nullptr;
  Node* end_ = nullptr;
  size_type size_ = 0;
};
}  // namespace s21

#endif