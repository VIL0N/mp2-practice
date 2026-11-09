#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix)
{
  TDynamicMatrix<int> m(5);

  ASSERT_NO_THROW(TDynamicMatrix<int> m1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);
	ASSERT_TRUE(m==m1);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> m(5);
	TDynamicMatrix<int> m1(m);
	int tmp[5]{ 1, 2, 3, 4, 5 };
	TDynamicVector<int> v (tmp, 5);
	m[0] = v;
	EXPECT_NE(m[0], m1[0]);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(5);
	ASSERT_EQ(m.size(), 5);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> m(5);
	int tmp[5]{ 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(tmp, 5);
	ASSERT_NO_THROW(m[0]=v);
	ASSERT_EQ(m[0], v);

}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> m(5);
	int tmp[5]{ 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(tmp, 5);
	ASSERT_ANY_THROW(m.at(-1) = v);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> m(5);
	int tmp[5]{ 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(tmp, 5);
	ASSERT_ANY_THROW(m.at(MAX_MATRIX_SIZE),v);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(m = m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	ASSERT_NO_THROW(m1 = m2);
	int tmp[5]{ 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(tmp, 5);
	m1[0]=v;
	ASSERT_NE(m1[0], m2[0]);

}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(10);
	ASSERT_NO_THROW(m1 = m2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(10);
	m1 = m2;
	ASSERT_EQ(m1.size(), m2.size());
}



TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);

	ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> m1(5);
	ASSERT_TRUE(m1 == m1);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(10);

	ASSERT_FALSE(m1 == m2);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	int tmp[5]{ 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(tmp, 5);
	m1[0]=v;
	m2[0]=v;
	ASSERT_NO_THROW(m1 + m2);
	EXPECT_EQ(m1[0] + m2[0], v + v);

}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(10);
	ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(5);
	int tmp[5]{ 1, 2, 3, 4, 5 };
	TDynamicVector<int> v(tmp, 5);
	ASSERT_NO_THROW(m1 - m2);
	m1[0] = v;
	m2[0]=v;
	EXPECT_EQ(m1[0] - m2[0], v-v);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(10);
	ASSERT_ANY_THROW(m1 - m2);
}
TEST(TDynamicMatrix, can_mult_matrix_equal_size) {
	TDynamicMatrix<int> m1(5, 1);
	TDynamicMatrix<int> m2(5, 2);
	ASSERT_NO_THROW(m1*m2);
	TDynamicMatrix<int> m3(m1 * m2);
	EXPECT_EQ(m3[0][0], 2);
}
TEST(TDynamicMatrix, cant_mult_matrix_dif_size) {
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m2(10);
	ASSERT_ANY_THROW(m1 * m2);
}
TEST(TDynamicMatrix, can_mult_matrix_vector_equal_size) {
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m3(5);
	int tmp1[5]{ 1, 2, 3, 4, 5 };
	int tmp2[5]{ 55 };

	TDynamicVector<int> v(tmp1, 5);
	for (int i = 0; i < m1.size(); i++) {
		m1[i] = v;
		m3[i] = v;
	}
	ASSERT_NO_THROW(m1 * v);
	EXPECT_EQ(m1, m3);
}

TEST(TDynamicMatrix, can_mult_matrix_vector_dif_size) {
	TDynamicMatrix<int> m1(5);
	TDynamicMatrix<int> m3(5);
	int tmp1[6]{ 1, 2, 3, 4, 5, 6 };
	TDynamicVector<int> v(tmp1, 6);
	ASSERT_ANY_THROW(m1 * v);

}