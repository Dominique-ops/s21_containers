#include <gtest/gtest.h>

#include <list>
#include <map>
#include <queue>
#include <set>
#include <stack>
#include <vector>

#include "./s21_containers/s21_containers.h"

// VECTOR
TEST(VectorTest, Constructor_default) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.data(), std_v.data());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_n) {
  s21::vector<int> s21_v(5);
  std::vector<int> std_v(5);
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_n_throw) {
  try {
    s21::vector<int> s21_v(-1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(),
              std::string("cannot create s21::vector larger than max_size()"));
  }
}

TEST(VectorTest, Constructor_initializer_list_1) {
  s21::vector<int> s21_v{2, 3, 5, 7, 1};
  std::vector<int> std_v{2, 3, 5, 7, 1};
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
}

TEST(VectorTest, Constructor_initializer_list_2) {
  std::initializer_list<int> b;
  s21::vector<int> s21_v{b};
  std::vector<int> std_v{b};
  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Constructor_copy_1) {
  s21::vector<int> s21_v{2, 3, 5, 7, 1};
  std::vector<int> std_v{2, 3, 5, 7, 1};
  s21::vector<int> s21_copy(s21_v);
  std::vector<int> std_copy(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());
  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
  EXPECT_EQ(s21_copy.at(0), std_copy.at(0));
  EXPECT_EQ(s21_copy.at(1), std_copy.at(1));
  EXPECT_EQ(s21_copy.at(2), std_copy.at(2));
  EXPECT_EQ(s21_copy.at(3), std_copy.at(3));
  EXPECT_EQ(s21_copy.at(4), std_copy.at(4));
}

TEST(VectorTest, Constructor_copy_2) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_copy(s21_v);
  std::vector<int> std_v;
  std::vector<int> std_copy(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_copy.size(), std_copy.size());
  EXPECT_EQ(s21_copy.capacity(), std_copy.capacity());
  EXPECT_EQ(s21_copy.empty(), std_copy.empty());
}

TEST(VectorTest, Constructor_move_1) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_move(s21_v);
  std::vector<int> std_v;
  std::vector<int> std_move(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_move.capacity(), std_move.capacity());
  EXPECT_EQ(s21_move.empty(), std_move.empty());
}

TEST(VectorTest, Constructor_move_2) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21::vector<int> s21_move(s21_v);
  std::vector<int> std_v{1, 2, 3, 4, 5};
  std::vector<int> std_move(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
  EXPECT_EQ(s21_v.empty(), std_v.empty());

  EXPECT_EQ(s21_move.size(), std_move.size());
  EXPECT_EQ(s21_move.capacity(), std_move.capacity());
  EXPECT_EQ(s21_move.empty(), std_move.empty());
}

TEST(VectorTest, Destructor) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  s21_v.~vector();

  EXPECT_EQ(0, s21_v.size());
  EXPECT_EQ(0, s21_v.capacity());
  EXPECT_EQ(0, s21_v.data());
}

TEST(VectorTest, Operator_move_1) {
  s21::vector<int> s21_v1{1, 2, 3};
  s21::vector<int> s21_v2;
  s21_v2 = std::move(s21_v1);
  EXPECT_EQ(s21_v2.size(), 3);
  EXPECT_EQ(s21_v2.at(0), 1);
  EXPECT_EQ(s21_v2.at(1), 2);
  EXPECT_EQ(s21_v2.at(2), 3);
}

TEST(VectorTest, Operator_move_2) {
  s21::vector<int> s21_v1{1, 2, 3};
  s21::vector<int> s21_v2{4, 5, 6};
  s21_v2 = std::move(s21_v1);
  EXPECT_EQ(s21_v2.size(), 3);
  EXPECT_EQ(s21_v2.at(0), 1);
  EXPECT_EQ(s21_v2.at(1), 2);
  EXPECT_EQ(s21_v2.at(2), 3);
}

TEST(VectorTest, Element_at) {
  s21::vector<int> s21_v{1, 2, 3, 4, 5};
  std::vector<int> std_v{1, 2, 3, 4, 5};

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
}

TEST(VectorTest, Element_at_throw) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_ANY_THROW(s21_v.at(1));
  EXPECT_ANY_THROW(std_v.at(1));
}

TEST(VectorTest, Element_front) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v.front(), std_v.front());
}

TEST(VectorTest, Element_front_throw) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_ANY_THROW(s21_v.front());
}

TEST(VectorTest, Element_back) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v.back(), std_v.back());
}

TEST(VectorTest, Element_back_throw) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  EXPECT_ANY_THROW(s21_v.back());
}

TEST(VectorTest, Element_operator_square_brackets) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_EQ(s21_v[0], std_v[0]);
  EXPECT_EQ(s21_v[1], std_v[1]);
  EXPECT_EQ(s21_v[2], std_v[2]);
}

TEST(VectorTest, Element_operator_square_brackets_throw_1) {
  s21::vector<int> s21_v{1, 2, 3};
  EXPECT_ANY_THROW(s21_v[5]);
}

TEST(VectorTest, Element_operator_square_brackets_throw_2) {
  s21::vector<int> s21_v{1, 2, 3};
  EXPECT_ANY_THROW(s21_v[-1]);
}

TEST(VectorTest, Element_data) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(*s21_v.data(), *std_v.data());
}

TEST(VectorTest, Capacity_empty_1) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Capacity_empty_2) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.empty(), std_v.empty());
}

TEST(VectorTest, Capacity_size_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Capacity_size_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Capacity_capacity_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_capacity_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};

  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(2);
  std_v.reserve(2);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_3) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_reserve_4_throw) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  EXPECT_ANY_THROW(s21_v.reserve(-2));
  EXPECT_ANY_THROW(std_v.reserve(-2));
}

TEST(VectorTest, Capacity_shrink_to_fit_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Capacity_shrink_to_fit_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.reserve(10);
  std_v.reserve(10);
  s21_v.shrink_to_fit();
  std_v.shrink_to_fit();
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());
}

TEST(VectorTest, Modifiers_clear_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Modifiers_clear_2) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.clear();
  std_v.clear();

  EXPECT_EQ(s21_v.size(), std_v.size());
}

TEST(VectorTest, Modifiers_insert_1) {
  s21::vector<int> s21_v{1, 2, 3};
  std::vector<int> std_v{1, 2, 3};
  s21_v.insert(s21_v.begin() + 1, 5);
  std_v.insert(std_v.begin() + 1, 5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, Modifiers_insert_2) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.insert(s21_v.begin() + s21_v.size(), 100);
  std_v.insert(std_v.begin() + std_v.size(), 100);

  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorTest, Modifiers_insert_3) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.insert(s21_v.begin() + 10, 100);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_insert_4) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.insert(s21_v.begin() - 4, 100);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_erase_1) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  std::vector<int> std_v{1, 2, 3, 4};

  s21_v.erase(s21_v.begin() + 1);
  std_v.erase(std_v.begin() + 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
}

TEST(VectorTest, Modifiers_erase_2) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.begin());
  std_v.erase(std_v.begin());

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_erase_3) {
  s21::vector<int> s21_v{50, 10, 40, 20, 30};
  std::vector<int> std_v{50, 10, 40, 20, 30};
  s21_v.erase(s21_v.end() - 1);
  std_v.erase(std_v.end() - 1);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_erase_4) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.erase(s21_v.begin() - 1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_erase_5) {
  try {
    s21::vector<int> s21_v{50, 10, 40, 20, 30};
    s21_v.erase(s21_v.end() + 1);
    FAIL() << "Expected std::out_of_range";
  } catch (std::out_of_range const& err) {
    EXPECT_EQ(err.what(), std::string("Index out ot range"));
  }
}

TEST(VectorTest, Modifiers_push_back_1) {
  s21::vector<int> s21_v;
  std::vector<int> std_v;

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
}

TEST(VectorTest, Modifiers_push_back_2) {
  s21::vector<int> s21_v{1, 2};
  std::vector<int> std_v{1, 2};

  s21_v.push_back(2);
  s21_v.push_back(3);
  s21_v.push_back(4);
  s21_v.push_back(5);

  std_v.push_back(2);
  std_v.push_back(3);
  std_v.push_back(4);
  std_v.push_back(5);

  EXPECT_EQ(s21_v.at(0), std_v.at(0));
  EXPECT_EQ(s21_v.at(1), std_v.at(1));
  EXPECT_EQ(s21_v.at(2), std_v.at(2));
  EXPECT_EQ(s21_v.at(3), std_v.at(3));
  EXPECT_EQ(s21_v.at(4), std_v.at(4));
  EXPECT_EQ(s21_v.at(5), std_v.at(5));
}

TEST(VectorTest, Modifiers_pop_back_1) {
  s21::vector<int> s21_v{1, 2};

  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();

  EXPECT_EQ(s21_v.size(), 0);
  EXPECT_EQ(s21_v.capacity(), 2);
}

TEST(VectorTest, Modifiers_pop_back_2) {
  s21::vector<int> s21_v;

  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();
  s21_v.pop_back();

  EXPECT_EQ(s21_v.size(), 0);
  EXPECT_EQ(s21_v.capacity(), 0);
}

TEST(VectorTest, Modifiers_swap_1) {
  s21::vector<int> s21_v;
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v;
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_2) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy;

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy;

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_3) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy{1, 2};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Modifiers_swap_4) {
  s21::vector<int> s21_v{1, 2, 3, 4};
  s21::vector<int> s21_v_copy{1, 2, 3, 4, 5, 6};

  std::vector<int> std_v{1, 2, 3, 4};
  std::vector<int> std_v_copy{1, 2, 3, 4, 5, 6};

  s21_v_copy.swap(s21_v);
  std_v_copy.swap(std_v);

  EXPECT_EQ(s21_v.size(), std_v.size());
  EXPECT_EQ(s21_v.capacity(), std_v.capacity());

  EXPECT_EQ(s21_v_copy.size(), std_v_copy.size());
  EXPECT_EQ(s21_v_copy.capacity(), std_v_copy.capacity());
}

TEST(VectorTest, Helpers_add_memotysize_1) {
  int n = 1000;
  s21::vector<int> s21_v(n);
  s21_v.push_back(1);
  EXPECT_EQ(s21_v.size(), n + 1);
}

TEST(VectorTest, Helpers_add_memotysize_2) {
  int n = 10000;
  s21::vector<int> s21_v(n);
  s21_v.push_back(1);

  EXPECT_EQ(s21_v.size(), n + 1);
}

TEST(VectorTest, Helpers_add_memotysize_3) {
  int n = 100000;
  s21::vector<int> s21_v(n);
  s21_v.push_back(1);
  s21_v.push_back(1);
  s21_v.push_back(1);

  EXPECT_EQ(s21_v.size(), n + 3);
}

TEST(setTest, DefaultConstructor) {
  s21::set<int> s;
  EXPECT_TRUE(s.empty());
  EXPECT_EQ(s.size(), 0);
}

TEST(setTest, InitializerListConstructor) {
  s21::set<int> s = {1, 2, 3};
  EXPECT_EQ(s.size(), 3);
  EXPECT_TRUE(s.contains(1));
  EXPECT_TRUE(s.contains(2));
  EXPECT_TRUE(s.contains(3));
}

TEST(setTest, CopyConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(s1);
  EXPECT_EQ(s1.size(), s2.size());
}

TEST(setTest, MoveConstructor) {
  s21::set<int> s1 = {1, 2, 3};
  s21::set<int> s2(std::move(s1));
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s2.contains(2));
  EXPECT_TRUE(s2.contains(3));
}
TEST(setTest, BeginEnd) {
  s21::set<int> s{3, 5, 1, 4, 2};
  auto it = s.begin();
  ASSERT_EQ(*it, 1);

  it = s.end();
  ASSERT_EQ(it, nullptr);

  s.clear();
  it = s.begin();
  ASSERT_EQ(it, nullptr);
}

TEST(setTest, SizeMaxSize) {
  s21::set<int> s{3, 5, 1, 4, 2};
  std::set<int> s1{3, 5, 1, 4, 2};
  ASSERT_EQ(s.size(), 5);
  ASSERT_GE(s.max_size(), s1.max_size());

  s.clear();
  ASSERT_EQ(s.size(), 0);
}
TEST(setTest, Erase) {
  s21::set<int> s{1, 2, 3, 4, 5};
  auto it = s.find(3);
  s.erase(it);
  EXPECT_EQ(s.size(), 4);
  EXPECT_FALSE(s.contains(3));
}

TEST(setTest, Swap) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{4, 5, 6};
  s1.swap(s2);
  EXPECT_EQ(s1.size(), 3);
  EXPECT_EQ(s2.size(), 3);
  EXPECT_TRUE(s2.contains(1));
  EXPECT_TRUE(s1.contains(4));
}

TEST(setTest, Merge) {
  s21::set<int> s1{1, 2, 3};
  s21::set<int> s2{3, 4, 5};
  s1.merge(s2);
  EXPECT_EQ(s1.size(), 5);
  EXPECT_EQ(s2.size(), 0);
  EXPECT_TRUE(s1.contains(4));
  EXPECT_FALSE(s2.contains(3));
}

TEST(setTest, Find) {
  s21::set<int> s{1, 2, 3};
  auto it1 = s.find(2);
  EXPECT_EQ(*it1, 2);
  auto it2 = s.find(4);
  EXPECT_EQ(it2, s.end());
}

TEST(mapConstructorTest, DefaultConstructor) {
  s21::map<int, std::string> m;
  EXPECT_EQ(m.size(), 0);
  EXPECT_TRUE(m.empty());
}

TEST(mapConstructorTest, InitializerListConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  EXPECT_EQ(m.size(), 3);
  EXPECT_FALSE(m.empty());
  EXPECT_EQ(m.at(1), "one");
  EXPECT_EQ(m.at(2), "two");
  EXPECT_EQ(m.at(3), "three");
}

TEST(mapConstructorTest, CopyConstructor) {
  s21::map<int, std::string> m{{1, "one"}, {2, "two"}, {3, "three"}};
  s21::map<int, std::string> copy_m(m);
  EXPECT_EQ(copy_m.size(), 3);
  EXPECT_FALSE(copy_m.empty());
  EXPECT_EQ(copy_m.at(1), "one");
}
// Test the insert(key, value) function
TEST(mapTest, InsertKeyValue) {
  s21::map<int, std::string> map;
  // Insert a single key-value pair
  map.insert(1, "one");
  // Check that the size is correct
  EXPECT_EQ(map.size(), 1);
  // Check that the inserted key-value pair is in the map
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  // Insert another key-value pair
  map.insert(2, "two");
  // Check that the size is correct
  EXPECT_EQ(map.size(), 2);
  // Check that both inserted key-value pairs are in the map
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}
// Test the insert(pair) function
TEST(mapTest, InsertPair) {
  s21::map<int, std::string> map;
  // Insert a single key-value pair using a pair object
  map.insert(std::make_pair(1, "one"));
  // Check that the size is correct
  EXPECT_EQ(map.size(), 1);
  // Check that the inserted key-value pair is in the map
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  // Insert another key-value pair using a pair object
  map.insert(std::make_pair(2, "two"));
  // Check that the size is correct
  EXPECT_EQ(map.size(), 2);
  // Check that both inserted key-value pairs are in the map
  EXPECT_EQ(map.contains(1), true);
  EXPECT_EQ(map[1], "one");
  EXPECT_EQ(map.contains(2), true);
  EXPECT_EQ(map[2], "two");
}
TEST(mapTest, InsertOrAssign) {
  s21::map<int, std::string> map;
  // Insert a new element with a key that does not exist.
  auto [it1, inserted1] = map.insert_or_assign(1, "one");
  EXPECT_TRUE(inserted1);
  EXPECT_EQ(it1->first, 1);
  EXPECT_EQ(it1->second, "one");
  // Insert a new element with a key that already exists.
  auto [it2, inserted2] = map.insert_or_assign(1, "ONE");
  EXPECT_FALSE(inserted2);
  EXPECT_EQ(it2->first, 1);
  EXPECT_EQ(it2->second, "ONE");
  // Insert multiple elements.
  map.insert_or_assign(2, "two");
  map.insert_or_assign(3, "three");
  map.insert_or_assign(4, "four");
  map.insert_or_assign(5, "five");
  EXPECT_EQ(map.size(), 5);
  EXPECT_EQ(map[1], "ONE");
  EXPECT_EQ(map[2], "two");
  EXPECT_EQ(map[3], "three");
  EXPECT_EQ(map[4], "four");
  EXPECT_EQ(map[5], "five");
}
TEST(mapTest, AtAndOperatorBrackets) {
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_EQ(map.at(1), "one");
  EXPECT_EQ(map[2], "two");
  EXPECT_THROW(map.at(4), std::invalid_argument);
  map[4] = "four";
  EXPECT_EQ(map[4], "four");
  map[2] = "TWO";
  EXPECT_EQ(map[2], "TWO");
}

TEST(mapTest, EmptyAndSize) {
  s21::map<int, std::string> empty_map;
  s21::map<int, std::string> map = {{1, "one"}, {2, "two"}, {3, "three"}};

  EXPECT_TRUE(empty_map.empty());
  EXPECT_EQ(empty_map.size(), 0);

  EXPECT_FALSE(map.empty());
  EXPECT_EQ(map.size(), 3);
}

TEST(mapTest, MaxSize) {
  s21::map<int, std::string> map;
  std::map<int, std::string> map1;

  // Max size is implementation-dependent, but it should be greater than 0
  EXPECT_GT(map.max_size(), map1.max_size());
}
TEST(mapTest, Erase) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  map.insert({3, "three"});
  map.insert({5, "five"});

  // Erase an existing element.
  auto it1 = map.begin()++;
  map.erase(it1);
  EXPECT_EQ(map.size(), 3);
  EXPECT_FALSE(map.contains(1));
}

TEST(mapTest, Swap) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.swap(map2);

  EXPECT_EQ(map1.size(), 2);
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));

  EXPECT_EQ(map2.size(), 2);
  EXPECT_TRUE(map2.contains(1));
  EXPECT_TRUE(map2.contains(2));
}

TEST(mapTest, Merge) {
  s21::map<int, std::string> map1;
  map1.insert({1, "one"});
  map1.insert({2, "two"});

  s21::map<int, std::string> map2;
  map2.insert({3, "three"});
  map2.insert({4, "four"});

  map1.merge(map2);

  EXPECT_EQ(map1.size(), 4);
  EXPECT_TRUE(map1.contains(1));
  EXPECT_TRUE(map1.contains(2));
  EXPECT_TRUE(map1.contains(3));
  EXPECT_TRUE(map1.contains(4));
}

TEST(mapTest, Contains) {
  s21::map<int, std::string> map;

  map.insert({1, "one"});
  map.insert({2, "two"});
  EXPECT_TRUE(map.contains(2));
  EXPECT_FALSE(map.contains(3));
}
TEST(setTest, RotateCheck) {
  s21::set<int> s1 = {1, 2, 3, 6, 7, 8, 9, 99, -56};
  s1.insert(-1000);
  s1.insert(-10002);
  s1.insert(-100023);
  s1.insert(-100024);
  s1.insert(-100026);
}
TEST(setTest, RotateCheck2) {
  s21::set<int> s1 = {5, 3, 7, 2, 4, 6, 8};
  s1.erase(s1.begin());
}
TEST(setTest, Remove) {
  s21::AVLTree<int, int> tree;
  tree.Insert(5);
  tree.Insert(3);
  tree.Insert(7);
  tree.Insert(2);
  tree.Insert(4);
  tree.Insert(6);
  tree.Insert(8);
  tree.Remove(5);
  tree.Remove(6);
  tree.Remove(8);
}
TEST(AVLTreeTest, RemoveTest) {
  s21::AVLTree<int, int> tree;
  tree.Insert(10);
  tree.Insert(20);
  tree.Insert(30);
  tree.Insert(40);
  tree.Insert(50);
  // Remove a leaf node
  tree.Remove(50);
}
TEST(setTest, RotateCheck3) {
  s21::set<int> s1 = {5, 3, 7, 2, 4, 6, 8, 4, 6, 8, 9, 0, 1, 241325, 543565};
}

TEST(List, DefaultConstructor) {
  s21::list<int> s21_list;
  std::list<int> std_list;

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, ParamConstructor) {
  s21::list<int> s21_list(5);
  std::list<int> std_list(5);

  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, InitConstructor) {
  s21::list<int> s21_list = {1, 3, 5, 7};
  std::list<int> std_list = {1, 3, 5, 7};
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, CopyConstructor) {
  s21::list<int> s21_a = {1, 3, 5, 7};
  std::list<int> std_a = {1, 3, 5, 7};
  s21::list<int> s21_list(s21_a);
  std::list<int> std_list(std_a);
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());
}

TEST(List, MoveConstructor) {
  s21::list<int> s21_a = {1, 3, 5, 7};
  std::list<int> std_a = {1, 3, 5, 7};
  s21::list<int> s21_list(std::move(s21_a));
  std::list<int> std_list(std::move(std_a));
  EXPECT_EQ(s21_list.front(), std_list.front());
  EXPECT_EQ(s21_list.back(), std_list.back());
  EXPECT_EQ(s21_list.size(), std_list.size());
  EXPECT_EQ(s21_list.empty(), std_list.empty());

  EXPECT_EQ(s21_a.size(), std_a.size());
  EXPECT_EQ(s21_a.empty(), std_a.empty());
}

TEST(list, front_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.front(), s21_list1.front());
}

TEST(list, back_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.back(), s21_list1.back());
}

TEST(list, begin_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(*std_list1.begin(), *s21_list1.begin());
}

TEST(list, empty_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.empty(), s21_list1.empty());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.empty(), s21_list2.empty());
}

TEST(list, size_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std::list<int> std_list2;
  s21::list<int> s21_list2;

  EXPECT_EQ(std_list2.size(), s21_list2.size());
}

TEST(list, clear_function) {
  std::list<int> std_list1 = {1, 2, 3};
  s21::list<int> s21_list1 = {1, 2, 3};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.clear();
  s21_list1.clear();

  EXPECT_EQ(std_list1.size(), s21_list1.size());
}

TEST(list, push_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.push_back(6);
  s21_list1.push_back(6);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, pop_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.pop_back();
  s21_list1.pop_back();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, push_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.push_front(6);
  s21_list1.push_front(6);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, pop_front_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  std_list1.pop_front();
  s21_list1.pop_front();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, swap_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {5, 4, 3, 2, 1};
  s21::list<int> s21_list2 = {5, 4, 3, 2, 1};

  std_list1.swap(std_list2);
  s21_list1.swap(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());
  EXPECT_EQ(std_list2.size(), s21_list2.size());

  EXPECT_EQ(*std_list1.begin(), *s21_list1.begin());
  EXPECT_EQ(*std_list2.begin(), *s21_list2.begin());
}

TEST(list, merge_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std::list<int> std_list2 = {9, 8, 7};
  s21::list<int> s21_list2 = {9, 8, 7};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {9, 8, 7};
  s21_list1 = {9, 8, 7};

  std_list2 = {1, 2, 3, 4, 5};
  s21_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {1, 2, 3, 4, 5};
  s21_list1 = {1, 2, 3, 4, 5};

  std_list2 = {1, 2, 3, 4, 5};
  s21_list2 = {1, 2, 3, 4, 5};

  std_list1.merge(std_list2);
  s21_list1.merge(s21_list2);

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  s21::list<int> s21_list;
  std::list<int> std_list;

  std_list.merge(std_list1);
  s21_list.merge(s21_list1);

  EXPECT_EQ(std_list.size(), s21_list.size());

  s21_it = s21_list.begin();
  for (auto std_it = std_list.begin(); std_it != std_list.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, reverse_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  std_list1.reverse();
  s21_list1.reverse();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, unique_function) {
  std::list<int> std_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};
  s21::list<int> s21_list1 = {1, 2, 2, 3, 4, 5, 5, 5, 2};

  std_list1.unique();
  s21_list1.unique();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, sort_function) {
  std::list<int> std_list1 = {2, 7, 1, 3, 8, 2};
  s21::list<int> s21_list1 = {2, 7, 1, 3, 8, 2};

  std_list1.sort();
  s21_list1.sort();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }

  std_list1 = {9, 8, 7, 6, 5};
  s21_list1 = {9, 8, 7, 6, 5};

  std_list1.sort();
  s21_list1.sort();

  EXPECT_EQ(std_list1.size(), s21_list1.size());

  s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_back_function) {
  std::list<int> std_list1 = {1, 2, 3, 4, 5, 6, 7, 8};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  s21_list1.insert_many_back(6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

TEST(list, insert_many_front_function) {
  std::list<int> std_list1 = {6, 7, 8, 1, 2, 3, 4, 5};
  s21::list<int> s21_list1 = {1, 2, 3, 4, 5};

  s21_list1.insert_many_front(6, 7, 8);

  EXPECT_EQ(8, s21_list1.size());

  auto s21_it = s21_list1.begin();
  for (auto std_it = std_list1.begin(); std_it != std_list1.end();
       ++std_it, ++s21_it) {
    EXPECT_EQ(*std_it, *s21_it);
  }
}

template <typename value_type1, typename value_type2>
bool compare_queues(s21::queue<value_type1> my_queue,
                    std::queue<value_type2> std_queue) {
  bool res = (my_queue.size() == std_queue.size());
  while (!my_queue.empty() && !std_queue.empty()) {
    if (my_queue.front() != std_queue.front()) res = false;
    my_queue.pop();
    std_queue.pop();
  }
  return res;
}

TEST(queue, test_1) {
  s21::queue<int> A;
  ASSERT_TRUE(A.empty());
  ASSERT_EQ(A.size(), 0);
}

TEST(queue, test_2) {
  s21::queue<int> A{1, 2, 3, 4};
  std::queue<int> B;
  for (int i = 1; i < 5; ++i) B.push(i);
  EXPECT_TRUE(compare_queues(A, B));
}

TEST(queue, test_3) {
  s21::queue<char> A{'a', 'b', 'c'};
  std::queue<char> B;
  for (char i = 'b'; i < 'g'; ++i) B.push(i);
  EXPECT_FALSE(compare_queues(A, B));
}

TEST(queue, test_4) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  std::queue<char> D(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_5) {
  const s21::queue<char> A{'a', 'b', 'c'};
  const s21::queue<char> B(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_6) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B(std::move(A));
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D(std::move(C));
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_7) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = A;
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D = C;
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_8) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = A;
  std::queue<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::queue<int> D = C;
  EXPECT_FALSE(compare_queues(B, D));
}

TEST(queue, test_9) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = std::move(A);
  std::queue<int> C;
  for (int i = 0; i < 2; ++i) C.push(i);
  std::queue<int> D = std::move(C);
  EXPECT_FALSE(compare_queues(B, D));
}

TEST(queue, test_10) {
  s21::queue<char> A{'a', 'b', 'c'};
  s21::queue<char> B = std::move(A);
  std::queue<char> C;
  for (char i = 'a'; i < 'd'; ++i) C.push(i);
  const std::queue<char> D = std::move(C);
  EXPECT_TRUE(compare_queues(B, D));
}

TEST(queue, test_11) {
  s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('a', A.front());
}

TEST(queue, test_12) {
  const s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('a', A.front());
}

TEST(queue, test_13) {
  s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.back());
}
TEST(queue, test_14) {
  const s21::queue<char> A{'a', 'b', 'c'};
  EXPECT_EQ('c', A.back());
}

TEST(queue, test_16) {
  const s21::queue<int> A{6, 7, 8, 9, 78};
  EXPECT_EQ(5, A.size());
}

TEST(queue, test_17) {
  s21::queue<int> A{6, 7, 8, 9, 78};
  A.push(std::move(187));
  EXPECT_EQ(187, A.back());
}

TEST(queue, test_18) {
  s21::queue<int> A{6, 7, 8, 9, 78};
  A.pop();
  EXPECT_EQ(7, A.front());
}
TEST(queue, test_15) {
  s21::queue<char> A{'a', 'd', 'g'};
  s21::queue<char> B{'c', 'g', 'y'};
  std::queue<char> C;
  C.push('a');
  C.push('d');
  C.push('g');
  std::queue<char> D;
  D.push('c');
  D.push('g');
  D.push('y');
  A.swap(B);
  C.swap(D);
  EXPECT_TRUE(compare_queues(B, D));
  EXPECT_TRUE(compare_queues(A, C));
}

TEST(queue, func_insert_many_back_1) {
  std::queue<int> A;
  for (char i = 1; i < 9; ++i) A.push(i);
  s21::queue<int> B{1, 2, 3, 4, 5};

  B.insert_many_back(6, 7, 8);

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_queues(B, A));
}

TEST(stack, func_insert_many_back_2) {
  std::queue<char> A;
  for (char i = 'a'; i < 'd'; ++i) A.push(i);
  s21::queue<char> B;

  B.insert_many_back('a', 'b', 'c');

  EXPECT_EQ(B.size(), A.size());
  EXPECT_TRUE(compare_queues(B, A));
}

TEST(StackTest, stack) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  EXPECT_EQ(k.empty(), false);
}

TEST(StackTest, stackMove) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  s21::stack<int> l(std::move(k));
  s21::stack<int> q;
  EXPECT_EQ(q.empty(), true);
}

TEST(StackTest, stackSwap) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  s21::stack<int> l(std::move(k));
  s21::stack<int> q;
  q = std::move(l);
  s21::stack<int> m;
  m.swap(q);
  EXPECT_EQ(m.size(), 4);
}

TEST(StackTest, stackPushPop) {
  s21::stack<int> n = {1, 2, 3, 4};
  s21::stack<int> k(n);
  s21::stack<int> l(std::move(k));
  s21::stack<int> q;
  q = std::move(l);
  s21::stack<int> m;
  m.swap(q);
  m.push(5);
  m.insert_many_front(6);
  for (int i = 6; i > 0; i--) {
    EXPECT_EQ(m.top(), i);
    m.pop();
  }
}

int main(int argc, char* argv[]) {
  testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
