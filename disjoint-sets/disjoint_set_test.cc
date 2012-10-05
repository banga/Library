#include "disjoint_set.h"

#include <iostream>
#include <vector>

#include "gtest/gtest.h"

using lib::DisjointSet;
using std::vector;
using std::cout;
using std::endl;

TEST(DisjointSetTest, SingleElement) {
  DisjointSet<int> d(2);
  DisjointSet<int> *set = d.FindSet();

  ASSERT_NE(set, static_cast<DisjointSet<int>*>(0));
  EXPECT_EQ(set->key(), 2);
}

bool IsEven(int x) {
  return (x % 2) == 0;
}

TEST(DisjointSetTest, Union) {
  DisjointSet<int> even(2), odd(1);
  vector<DisjointSet<int>*> numbers;

  for (int i = 0; i < 100; ++i) {
    numbers.push_back(new DisjointSet<int>(i+2));
  }

  for (vector<DisjointSet<int>*>::iterator it = numbers.begin();
      it != numbers.end(); ++it) {
    if (IsEven((*it)->key())) {
      even.Union(*it);
    } else {
      odd.Union(*it);
    }
  }

  for (vector<DisjointSet<int>*>::iterator it = numbers.begin();
      it != numbers.end(); ++it) {
    DisjointSet<int> *set = (*it)->FindSet();
    ASSERT_NE(set, static_cast<DisjointSet<int>*>(0));

    int n = (*it)->key(), representative = set->key();
    EXPECT_EQ(IsEven(n), IsEven(representative));
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
