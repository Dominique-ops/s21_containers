#ifndef S21_ARRAY_H
#define S21_ARRAY_H
#include <exception>
#include <iostream>
namespace s21 {
template <typename T, std::size_t N>
class array {
 private:
  T pointer[N];
  size_t size_ = N;

 public:
  using value_type = T;
  using reference = T &;
  using const_reference = const T &;
  using iterator = T *;
  using const_iterator = const T *;
  using size_type = size_t;

  array() : size_(N) {
    for (size_type i = 0; i < size_; i++) {
      pointer[i] = 0;
    }
  };
  array(std::initializer_list<value_type> const &items);
  array(const array &a);
  array(array &&a);
  ~array() = default;
  array &operator=(array &&a);
  reference at(size_type pos);
  reference operator[](size_type pos);
  const_reference front();
  const_reference back();
  iterator data();
  iterator begin();
  iterator end();
  bool empty();
  size_type size();
  size_type max_size();
  void swap(array &other);
  void fill(const_reference value);
  array &operator=(array<T, N> &a);
};

template <typename T, std::size_t N>
s21::array<T, N>::array(std::initializer_list<value_type> const &items) {
  size_t j = 0;
  for (auto i = items.begin(); i != items.end(); ++i, j++) {
    pointer[j] = *i;
    if (j > N) throw std::length_error("too many arguments");
  }
}

template <typename T, std::size_t N>
s21::array<T, N>::array(const s21::array<T, N> &a) {
  std::cout << size_ << std::endl;
  for (size_t i = 0; i < N; i++) {
    this->pointer[i] = a.pointer[i];
  }
}
template <typename T, std::size_t N>
s21::array<T, N>::array(array<T, N> &&a) {
  std::move(a.pointer, a.pointer + N, pointer);
  a.size_ = 0;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &&a) {
  for (size_t i = 0; i < N; i++) {
    pointer[i] = std::move(a.pointer[i]);
  }
  return *this;
}

template <typename T, std::size_t N>
array<T, N> &array<T, N>::operator=(array<T, N> &a) {
  for (size_t i = 0; i < N; i++) {
    pointer[i] = a.pointer[i];
  }
  return *this;
}

template <typename T, std::size_t N>
T &array<T, N>::at(size_type pos) {
  if (pos > N) throw std::out_of_range("invalid argument");

  return (*this)[pos];
}

template <typename T, std::size_t N>
T &array<T, N>::operator[](size_type pos) {
  return pointer[pos];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::front() {
  return pointer[0];
}

template <typename T, std::size_t N>
typename array<T, N>::const_reference array<T, N>::back() {
  return pointer[size_ - 1];
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::data() {
  return pointer;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::begin() {
  return pointer;
}

template <typename T, std::size_t N>
typename array<T, N>::iterator array<T, N>::end() {
  return pointer + size_;
}

template <typename T, std::size_t N>
bool array<T, N>::empty() {
  return !size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::size() {
  return size_;
}

template <typename T, std::size_t N>
typename array<T, N>::size_type array<T, N>::max_size() {
  return size();
}

template <typename T, std::size_t N>
void array<T, N>::swap(array &other) {
  T temp;
  for (size_t i = 0; i < size_; i++) {
    temp = pointer[i];
    pointer[i] = other.pointer[i];
    other.pointer[i] = temp;
  }
}

template <typename T, std::size_t N>
void array<T, N>::fill(const_reference value) {
  for (size_t i = 0; i < size_; i++) {
    pointer[i] = value;
  }
}

}  // namespace s21
#endif