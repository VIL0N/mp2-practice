#include "tmatrix.h"

#include <gtest.h>
using namespace std;
const int CNT = 10;
TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(CNT));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-CNT));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(CNT);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> v(CNT);
	TDynamicVector<int> v1(v);
	ASSERT_EQ(v, v1);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> v(CNT);
	TDynamicVector<int> v1(v);
	v[0] = CNT;
	v1[0] = CNT-1;
	ASSERT_NE(v[0], v1[0]);
}

TEST(TDynamicVector, can_get_size)
{
  TDynamicVector<int> v(CNT);

  EXPECT_EQ(CNT, v.size());
}

//TEST(TDynamicVector, can_set_and_get_element)
//{
//  TDynamicVector<int> v(4);
//  v[0] = 4;
//
//  EXPECT_EQ(4, v[0]);
//}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
	TDynamicVector<int> v(CNT);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(CNT);
	ASSERT_ANY_THROW(v.at(MAX_VECTOR_SIZE));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(CNT);
	v[0] = CNT;
	ASSERT_NO_THROW(v = v);
	EXPECT_EQ(v[0], CNT);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> v1(CNT);
	for (int i = 0; i < v1.size(); i++) {
		v1[i] = i;
	}
	TDynamicVector<int> v2(CNT);
	for (int i = 0; i < v2.size(); i++) {
		v2[i] = i+1;
	}
	ASSERT_NO_THROW(v1 = v2);
	EXPECT_EQ(v1[0], 1);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> v1(CNT);
	v1[0] = 0;
	TDynamicVector<int> v2(CNT + CNT);
	v2[0] = 1;
	ASSERT_NO_THROW(v1 = v2);
	EXPECT_EQ(v1[0], 1);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT + CNT);
	v1 = v2;
	EXPECT_EQ(v1.size(), CNT+CNT);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT);
	for (int i = 0; i < CNT; i++) {
		v1[i] = i;
		v2[i] = i;
	}
	EXPECT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v1(CNT);
	EXPECT_TRUE(v1 == v1);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT+ CNT);
	EXPECT_FALSE(v1 == v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> v1(CNT);
	v1 = v1 + CNT;
	EXPECT_EQ(CNT, v1[0]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> v1(CNT);
	v1 = v1 - CNT;
	EXPECT_EQ(-CNT, v1[0]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> v1(CNT);
	v1[0] = 1;
	v1 = v1 * CNT;
	EXPECT_EQ(CNT, v1[0]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT);
	for (int i = 0; i < CNT; i++) {
		v1[i] = i;
		v2[i] = i+1;
	}
	ASSERT_NO_THROW(v1 + v2);
	EXPECT_EQ(v1[0]+v2[0], 1);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT+ CNT);
	ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT);
	for (int i = 0; i < CNT; i++) {
		v1[i] = i+1;
		v2[i] = i;
	}
	ASSERT_NO_THROW(v1 - v2);
	EXPECT_EQ(v1[3] - v2[3], 1);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT + CNT);
	ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT);
	ASSERT_NO_THROW(v1 * v2);
	v1[0] = 1;
	v2[0] = 2;
	EXPECT_EQ(2, v1 * v2);
}
TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	TDynamicVector<int> v1(CNT);
	TDynamicVector<int> v2(CNT + CNT);
	ASSERT_ANY_THROW(v1 * v2);
}

