#include <gtest/gtest.h>
#include <iostream>
#include "../lib_lqueue/lqueue.h"

TEST(TestLQueueLib, try_create_object) {
    ASSERT_NO_THROW(LQueue<int> object(10));
}

TEST(TestLQueueLib, try_create_object_2) {
    ASSERT_NO_THROW(LQueue<int> object);
}

TEST(TestLQueueLib, correct_create_object) {
    LQueue<int> object(10);

    EXPECT_EQ(0, object.size());
    EXPECT_EQ(10, object.capacity());
    EXPECT_EQ(0, object.head());
}

TEST(TestLQueueLib, correct_create_object_2) {
    LQueue<int> object;

    EXPECT_EQ(0, object.size());
    EXPECT_EQ(0, object.head());
}

TEST(TestLQueueLib, correct_create_object_with_copy) {
    LQueue<int> object(10);
    LQueue<int> object2(object);

    EXPECT_EQ(0, object2.size());
    EXPECT_EQ(10, object2.capacity());
    EXPECT_EQ(0, object.head());
}

TEST(TestLQueueLib, correct_create_object_with_copy_2) {
    LQueue<int> object;
    LQueue<int> object2(object);

    EXPECT_EQ(0, object2.size());
    EXPECT_EQ(0, object.head());
}

TEST(TestLQueueLib, correct_create_object_with_copy_3) {
    LQueue<int> object(5);
    object.push(222);
    LQueue<int> object2(object);

    EXPECT_EQ(1, object2.size());
    EXPECT_EQ(5, object2.capacity());
    EXPECT_EQ(222, object2.tail());
    EXPECT_EQ(222, object2.head());
}

TEST(TestLQueueLib, correct_create_object_with_copy_4) {
    LQueue<int> object;
    object.push(111);
    object.push(222);
    object.push(333);
    object.pop();
    object.push(444);
    LQueue<int> object2(object);

    EXPECT_EQ(444, object2.tail());
    EXPECT_EQ(222, object2.head());
}

TEST(TestLQueueLib, correct_is_empty) {
    LQueue<int> object;

    EXPECT_TRUE(object.is_empty());

    object.push(22);
    object.pop();

    EXPECT_TRUE(object.is_empty());

    object.push(111);
    object.push(222);
    object.clear();

    EXPECT_TRUE(object.is_empty());
}

TEST(TestLQueueLib, correct_clear) {
    LQueue<int> object(10);
    object.push(11);
    object.push(22);
    object.clear();

    EXPECT_EQ(0, object.head());
    EXPECT_EQ(0, object.size());
    EXPECT_EQ(10, object.capacity());

    ASSERT_NO_THROW(object.push(22));
}

TEST(TestLQueueLib, correct_is_full_and_is_empty) {
    size_t size = 5;
    LQueue<int> object(size);

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

TEST(TestLQueueLib, correct_is_full) {
    LQueue<int> object;

    EXPECT_FALSE(object.is_full());

    for (int i = 0; i < 3; i++) {
        object.push(11);
        EXPECT_FALSE(object.is_full());
    }
}

TEST(TestLQueueLib, throw_push) {
    LQueue<int> object(3);
    object.push(11);
    object.push(22);
    object.push(33);

    ASSERT_THROW(object.push(11), std::logic_error);
}

TEST(TestLQueueLib, throw_pop) {
    LQueue<int> object;

    ASSERT_THROW(object.pop(), std::logic_error);
}

TEST(TestLQueueLib, correct_push_and_pop_and_count) {
    LQueue<int> object(10);
    object.push(55);
    object.push(44);
    object.push(33);

    EXPECT_EQ(33, object.tail());

    object.pop();
    object.push(22);
    object.push(11);

    EXPECT_EQ(11, object.tail());
    EXPECT_EQ(44, object.head());

    object.pop();

    EXPECT_EQ(33, object.head());

    object.pop();

    EXPECT_EQ(22, object.head());
}

TEST(TestLQueueLib, correct_push_and_pop_and_count_2) {
    LQueue<int> object(5);
    object.push(55);
    object.push(44);
    object.push(33);

    EXPECT_EQ(33, object.tail());

    object.pop();
    object.push(22);
    object.push(11);
    object.push(1);

    EXPECT_TRUE(object.is_full());
    EXPECT_EQ(1, object.tail());
    EXPECT_EQ(44, object.head());
    ASSERT_THROW(object.push(111), std::logic_error);

    object.pop();
    object.push(2);

    EXPECT_TRUE(object.is_full());
    EXPECT_EQ(2, object.tail());
    EXPECT_EQ(33, object.head());
    ASSERT_THROW(object.push(111), std::logic_error);
}
