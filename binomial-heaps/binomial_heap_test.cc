#include "binomial_heap.h"

#include <algorithm>
#include <vector>

#include "gtest/gtest.h"

using std::vector;
using lib::BinomialHeap;

int L1[] = {2, 17, 34, 52, 41, 77};
int size1 = 6;

int L2[] = {14, 54, 90, 3, 12};
int size2 = 5;

// Tests operations on empty heap
TEST(BinomialHeapTest, EmptyHeap) {
  BinomialHeap<int> emptyHeap1;
  ASSERT_FALSE(emptyHeap1.ExtractMinimum(0));

  BinomialHeap<int> emptyHeap2;
  ASSERT_FALSE(emptyHeap2.ExtractMinimum(0));

  emptyHeap1.Union(&emptyHeap2);
  ASSERT_FALSE(emptyHeap1.ExtractMinimum(0));
}

// Tests insertions
TEST(BinomialHeapTest, Insert) {
  BinomialHeap<int> heap;

  int min;
  for (int i = 0; i < size1; ++i) {
    heap.Insert(L1[i]);
    ASSERT_TRUE(heap.ExtractMinimum(&min));
    ASSERT_EQ(min, L1[i]);
  }
}

// Tests that minimum values are returned
TEST(BinomialHeapTest, Minimum) {
  BinomialHeap<int> heap;

  vector<int> sortedL1(L1, L1 + size1);
  std::sort(sortedL1.begin(), sortedL1.end());

  for (int i = 0; i < size1; ++i) {
    heap.Insert(L1[i]);
  }

  int min;
  for (int i = 0; i < size1; ++i) {
    ASSERT_TRUE(heap.ExtractMinimum(&min));
    ASSERT_EQ(min, sortedL1[i]);
  }
}

// Tests the union operation
TEST(BinomialHeapTest, Union) {
  BinomialHeap<int> heap1;
  for (int i = 0; i < size1; ++i) {
    heap1.Insert(L1[i]);
  }

  BinomialHeap<int> heap2;
  for (int i = 0; i < size2; ++i) {
    heap2.Insert(L2[i]);
  }

  heap1.Union(&heap2);

  vector<int> sortedUnion(L1, L1 + size1);
  for (int i = 0; i < size2; ++i)
    sortedUnion.push_back(L2[i]);
  std::sort(sortedUnion.begin(), sortedUnion.end());

  int min;
  for (int i = 0; i < size1+size2; ++i) {
    ASSERT_TRUE(heap1.ExtractMinimum(&min));
    ASSERT_EQ(min, sortedUnion[i]);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
