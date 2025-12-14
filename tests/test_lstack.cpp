#include <gtest/gtest.h>
#include <iostream>
#include "../lib_lstack/lstack.h"

TEST(TestLStackLib, try_create_object) {
    ASSERT_NO_THROW(LStack<int> object);
}

TEST(TestLStackLib, try_create_object_2) {
    ASSERT_NO_THROW(LStack<int> object(100));
}

TEST(TestLStackLib, correct_create_object) {
    LStack<int> object;

    EXPECT_EQ(0, object.size());
    EXPECT_EQ(0, object.top());
}

TEST(TestLStackLib, correct_create_object_2) {
    LStack<int> object(20);

    EXPECT_EQ(20, object.capacity());
    EXPECT_EQ(0, object.top());
    EXPECT_EQ(0, object.size());
}

TEST(TestLStackLib, correct_create_object_with_copy) {
    LStack<int> object;
    LStack<int> object2(object);

    EXPECT_EQ(0, object2.size());
    EXPECT_EQ(0, object2.top());
}

TEST(TestLStackLib, correct_create_object_with_copy_2) {
    LStack<int> object;
    object.push(111);
    object.push(222);
    LStack<int> object2(object);

    EXPECT_EQ(2, object2.size());
    EXPECT_EQ(222, object2.top());
}

TEST(TestLStackLib, correct_create_object_with_copy_3) {
    LStack<int> object(10);
    object.push(111);
    object.push(222);
    LStack<int> object2(object);

    EXPECT_EQ(10, object2.capacity());
    EXPECT_EQ(2, object2.size());
    EXPECT_EQ(222, object2.top());
}

TEST(TestLStackLib, correct_push) {
    LStack<int> object;
    object.push(55);

    EXPECT_EQ(55, object.top());
}

TEST(TestLStackLib, throw_push) {
    LStack<int> object(3);
    object.push(11);
    object.push(22);
    object.push(33);

    ASSERT_THROW(object.push(11), std::logic_error);
}

TEST(TestLStackLib, throw_pop) {
    LStack<int> object;

    ASSERT_THROW(object.pop(), std::logic_error);
}

TEST(TestLStackLib, correct_pop) {
    LStack<int> object;
    object.push(55);
    object.push(44);
    object.push(33);
    object.pop();

    EXPECT_EQ(44, object.top());
}

TEST(TestLStackLib, correct_push_and_pop) {
    LStack<int> object;
    object.push(55);
    object.push(44);
    object.push(33);

    EXPECT_EQ(33, object.top());

    object.pop();
    object.push(22);
    object.push(11);

    EXPECT_EQ(11, object.top());

    object.pop();

    EXPECT_EQ(22, object.top());

    object.pop();

    EXPECT_EQ(44, object.top());

    object.push(111);

    EXPECT_EQ(111, object.top());
}

TEST(TestLStackLib, correct_is_empty) {
    LStack<int> object;

    EXPECT_TRUE(object.is_empty());

    object.push(22);
    object.pop();

    EXPECT_TRUE(object.is_empty());

    object.push(111);
    object.push(222);
    object.clear();

    EXPECT_TRUE(object.is_empty());
}

TEST(TestLStackLib, correct_is_full_and_is_empty) {
    size_t size = 5;
    LStack<int> object(size);

    EXPECT_FALSE(object.is_full());
    EXPECT_TRUE(object.is_empty());

    for (int i = 0; i < size; i++) {
        object.push(i + 1);
    }
    EXPECT_TRUE(object.is_full());
    EXPECT_FALSE(object.is_empty());

    object.pop();

    EXPECT_FALSE(object.is_full());
    EXPECT_FALSE(object.is_empty());
}

TEST(TestLStackLib, correct_is_full) {
    LStack<int> object;

    EXPECT_FALSE(object.is_full());

    for (int i = 0; i < 3; i++) {
        object.push(11);
        EXPECT_FALSE(object.is_full());
    }
}

TEST(TestLStackLib, correct_clear) {
    LStack<int> object;
    object.push(11);
    object.push(22);
    object.clear();

    EXPECT_EQ(0, object.top());
    EXPECT_EQ(0, object.size());

    ASSERT_NO_THROW(object.push(22));
}

TEST(TestLStackLib, correct_clear_2) {
    LStack<int> object(10);
    object.push(11);
    object.push(22);
    object.clear();

    EXPECT_EQ(0, object.top());
    EXPECT_EQ(0, object.size());
    EXPECT_EQ(10, object.capacity());

    ASSERT_NO_THROW(object.push(22));
}