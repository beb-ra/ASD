#include <gtest/gtest.h>
#include <iostream>
#include "../lib_stack/stack.h"

TEST(TestStackLib, try_create_object) {
    ASSERT_NO_THROW(Stack<int> object(10));
}

TEST(TestStackLib, try_create_object_with_copy) {
    Stack<int> object(10);

    ASSERT_NO_THROW(Stack<int> object2(object));
}

TEST(TestStackLib, correct_create_object) {
    Stack<int> object(10);

    EXPECT_EQ(10, object.size());
    EXPECT_EQ(-1, object.top());
}

TEST(TestStackLib, correct_create_object_with_copy) {
    Stack<int> object(10);
    Stack<int> object2(object);

    EXPECT_EQ(10, object2.size());
    EXPECT_EQ(-1, object2.top());
}

TEST(TestStackLib, correct_create_object_with_copy_2) {
    Stack<int> object(5);
    object.push(222);
    Stack<int> object2(object);

    EXPECT_EQ(5, object2.size());
    EXPECT_EQ(222, object2.top());
}

TEST(TestStackLib, correct_push) {
    Stack<int> object(10);
    object.push(55);

    EXPECT_EQ(55, object.top());
}

TEST(TestStackLib, correct_pop) {
    Stack<int> object(10);
    object.push(55);
    object.push(44);
    object.push(33);
    object.pop();

    EXPECT_EQ(44, object.top());
}

TEST(TestStackLib, correct_push_and_pop) {
    Stack<int> object(10);
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

TEST(TestStackLib, correct_top) {
    Stack<int> object(10);

    EXPECT_EQ(-1, object.top());
}

TEST(TestStackLib, correct_is_empty) {
    Stack<int> object(10);

    EXPECT_TRUE(object.is_empty());

    object.push(22);
    object.pop();

    EXPECT_TRUE(object.is_empty());

    object.push(111);
    object.push(222);
    object.clear();

    EXPECT_TRUE(object.is_empty());
}

TEST(TestStackLib, correct_is_full_and_is_empty) {
    size_t size = 5;
    Stack<int> object(size);

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


TEST(TestStackLib, correct_clear) {
    Stack<int> object(10);
    object.push(11);
    object.push(22);
    object.clear();

    EXPECT_EQ(-1, object.top());
    EXPECT_EQ(10, object.size());
}
