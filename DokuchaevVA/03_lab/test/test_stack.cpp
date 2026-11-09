#include <gtest.h>
#include "stack.h"

TEST(stack_test, can_create_stack) {
    ASSERT_NO_THROW(stack<int> st(5));
}
TEST(stack_test, cant_create_stack_zero_size) {
    ASSERT_ANY_THROW(stack<int> st(0));
}