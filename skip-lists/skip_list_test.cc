#include <iostream>
#include <string>

#include "skip_list.h"
#include "gtest/gtest.h"

using lib::SkipList;

int Keys[] = {3, 1, 2, 4};
const char* Values[] = { "Three", "One", "Two", "Four" };
int ItemCount = 4;

int NonKeys[] = {27, 0, -1, 100000};
int NonKeyCount = 4;

TEST(SkipListTest, InitialState) {
  SkipList<int, std::string> list;
  ASSERT_EQ(list.Size(), 0);
}

TEST(SkipListTest, SingleInsert) {
  SkipList<int, std::string> list;
  list.Insert(Keys[0], Values[0]);
  ASSERT_EQ(list.Size(), 1);
}

TEST(SkipListTest, MultipleInsert) {
  SkipList<int, std::string> list;
  for (int i = 0; i < ItemCount; ++i)
    list.Insert(Keys[i], Values[i]);
  ASSERT_EQ(list.Size(), ItemCount);
}

TEST(SkipListTest, SimpleDelete) {
  SkipList<int, std::string> list;
  list.Insert(Keys[0], Values[0]);
  list.Delete(Keys[0]);
  ASSERT_EQ(list.Size(), 0);
}

TEST(SkipListTest, MultipleDelete) {
  SkipList<int, std::string> list;
  for (int i = 0; i < ItemCount; ++i)
    list.Insert(Keys[i], Values[i]);
  for (int i = 0; i < ItemCount; ++i)
    list.Delete(Keys[i]);
  ASSERT_EQ(list.Size(), 0);
}

TEST(SkipListTest, DeleteNonExisting) {
  SkipList<int, std::string> list;
  for (int i = 0; i < ItemCount; ++i)
    list.Insert(Keys[i], Values[i]);
  for (int i = 0; i < ItemCount; ++i)
    list.Delete(Keys[i]);
  for (int i = 0; i < NonKeyCount; ++i)
    list.Delete(NonKeys[i]);
  ASSERT_EQ(list.Size(), 0);
}

TEST(SkipListTest, SimpleFind) {
  SkipList<int, std::string> list;
  list.Insert(Keys[0], Values[0]);
  std::string *p = list.Find(Keys[0]);
  ASSERT_NE(p, (std::string*)0);
  ASSERT_EQ(*p, Values[0]);
}

TEST(SkipListTest, MultipleFind) {
  SkipList<int, std::string> list;
  for (int i = 0; i < ItemCount; ++i)
    list.Insert(Keys[i], Values[i]);
  for (int i = 0; i < ItemCount; ++i) {
    std::string *p = list.Find(Keys[i]);
    ASSERT_NE(p, (std::string*)0);
    ASSERT_EQ(*p, Values[i]);
  }
  for (int i = 0; i < NonKeyCount; ++i) {
    std::string *p = list.Find(NonKeys[i]);
    ASSERT_EQ(p, (std::string*)0);
  }
}

int main(int argc, char **argv) {
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}
