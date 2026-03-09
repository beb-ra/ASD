#include <gtest/gtest.h>
#include <iostream>
#include "../lib_queue/queue.h"


TEST(TestQueueLib, try_create_object) {
    ASSERT_NO_THROW(Queue<int> object(10));
}

TEST(TestQueueLib, try_create_object_with_copy) {
    Queue<int> object(10);

    ASSERT_NO_THROW(Queue<int> object2(object));
}

TEST(TestQueueLib, correct_create_object) {
    Queue<int> object(10);

    EXPECT_EQ(10, object.size());
    EXPECT_EQ(0, object.count());
    EXPECT_THROW(object.head(), std::out_of_range);
}

TEST(TestQueueLib, correct_create_object_with_copy) {
    Queue<int> object(10);
    Queue<int> object2(object);

    EXPECT_EQ(10, object2.size());
    EXPECT_EQ(0, object.count());
    EXPECT_THROW(object.head(), std::out_of_range);
}

TEST(TestQueueLib, correct_create_object_with_copy_2) {
    Queue<int> object(5);
    object.push(222);
    Queue<int> object2(object);

    EXPECT_EQ(5, object2.size());
    EXPECT_EQ(222, object2.tail());
    EXPECT_EQ(222, object2.head());
}

TEST(TestQueueLib, correct_create_object_with_copy_3) {
    Queue<int> object(3);
    object.push(111);
    object.push(222);
    object.push(333);
    object.pop();
    object.push(444);
    Queue<int> object2(object);

    EXPECT_EQ(444, object2.tail());
    EXPECT_EQ(222, object2.head());
}

TEST(TestQueueLib, correct_is_empty) {
    Queue<int> object(10);

    EXPECT_TRUE(object.is_empty());

    object.push(22);
    object.pop();

    EXPECT_TRUE(object.is_empty());

    object.push(111);
    object.push(222);
    object.clear();

    EXPECT_TRUE(object.is_empty());
}

TEST(TestQueueLib, correct_clear) {
    Queue<int> object(10);
    object.push(11);
    object.push(22);
    object.clear();

    EXPECT_EQ(0, object.count());
    EXPECT_EQ(10, object.size());
    EXPECT_THROW(object.head(), std::out_of_range);

    ASSERT_NO_THROW(object.push(22));
}

TEST(TestQueueLib, correct_is_full_and_is_empty) {
    size_t size = 5;
    Queue<int> object(size);

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

TEST(TestQueueLib, throw_push) {
    Queue<int> object(3);
    object.push(11);
    object.push(22);
    object.push(33);

    ASSERT_THROW(object.push(11), std::logic_error);
}

TEST(TestQueueLib, throw_pop) {
    Queue<int> object(10);

    ASSERT_THROW(object.pop(), std::logic_error);
}

TEST(TestQueueLib, correct_push_and_pop_and_count) {
    Queue<int> object(10);
    object.push(55);
    object.push(44);
    object.push(33);

    EXPECT_EQ(33, object.tail());
    EXPECT_EQ(3, object.count());

    object.pop();
    object.push(22);
    object.push(11);

    EXPECT_EQ(4, object.count());
    EXPECT_EQ(11, object.tail());
    EXPECT_EQ(44, object.head());

    object.pop();

    EXPECT_EQ(3, object.count());
    EXPECT_EQ(33, object.head());

    object.pop();

    EXPECT_EQ(2, object.count());
    EXPECT_EQ(22, object.head());
}

TEST(TestQueueLib, correct_push_and_pop_and_count_2) {
    Queue<int> object(5);
    object.push(55);
    object.push(44);
    object.push(33);

    EXPECT_EQ(33, object.tail());
    EXPECT_EQ(3, object.count());

    object.pop();
    object.push(22);
    object.push(11);
    object.push(1);

    EXPECT_EQ(5, object.count());
    EXPECT_TRUE(object.is_full());
    EXPECT_EQ(1, object.tail());
    EXPECT_EQ(44, object.head());
    ASSERT_THROW(object.push(111), std::logic_error);  /////////////////////////

    object.pop();
    object.push(2);
    //std::cout << "AAAAAAAAAAAAAAAAAAAAA";

    EXPECT_EQ(5, object.count());
    EXPECT_TRUE(object.is_full());
    EXPECT_EQ(2, object.tail());
    EXPECT_EQ(33, object.head());
    ASSERT_THROW(object.push(111), std::logic_error);
}