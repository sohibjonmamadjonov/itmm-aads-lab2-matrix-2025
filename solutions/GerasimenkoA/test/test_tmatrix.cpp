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
	TDynamicMatrix<int> a(10), b(10);
	for (size_t i = 0; i < 10; ++i) {
		for (size_t j = 0; j < 10; ++j) {
			a[i][j] = 1;
			b[i][j] = 2;
		}
	}
	a = b;
	EXPECT_EQ(a, b);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
	TDynamicMatrix<int> a(4);
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			a[i][j] = static_cast<int>(i + 1);
		}
	}

	TDynamicMatrix<int> b(a);
	b[0][0] = 100;

	ASSERT_EQ(1, a[0][0]);
	ASSERT_EQ(100, b[0][0]);
	ASSERT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_get_size)
{
	TDynamicMatrix<int> m(4);

	EXPECT_EQ(4, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
	TDynamicMatrix<int> v(4);
	v[0][0] = 4;

	EXPECT_EQ(4, v[0][0]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v[-1][-1]);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
	TDynamicMatrix<int> v(4);
	ASSERT_ANY_THROW(v[5][5]);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 1; v[0][1] = 2;
	v[1][0] = 3; v[1][1] = 4;
	v = v;
	EXPECT_EQ(1, v[0][0]);
	EXPECT_EQ(2, v[0][1]);
	EXPECT_EQ(3, v[1][0]);
	EXPECT_EQ(4, v[1][1]);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
	TDynamicMatrix<int> a(4), b(4);
	ASSERT_NO_THROW(a = b);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
	TDynamicMatrix<int> a(3), b(4);
	a = b;
	EXPECT_EQ(b.size(), a.size());
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
	TDynamicMatrix<int> a(3), b(4);
	ASSERT_NO_THROW(a = b);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
	TDynamicMatrix<int> v(2), b(2);
	v[0][0] = 1; v[0][1] = 2;
	v[1][0] = 3; v[1][1] = 4;

	b[0][0] = 1; b[0][1] = 2;
	b[1][0] = 3; b[1][1] = 4;

	ASSERT_TRUE(v == b);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
	TDynamicMatrix<int> v(2);
	v[0][0] = 1; v[0][1] = 2;
	v[1][0] = 3; v[1][1] = 4;
	ASSERT_TRUE(v == v);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
	TDynamicMatrix<int> a(3), b(4);
	ASSERT_FALSE(a == b);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(4), b(4);
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			a[i][j] = static_cast<int>(i + 1);
			b[i][j] = static_cast<int>((i + 1) * 10);
		}
	}
	TDynamicMatrix<int> res;
	ASSERT_NO_THROW(res = a + b);
	EXPECT_EQ(a.size(), res.size());
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
	TDynamicMatrix<int> a(4), b(5);
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			a[i][j] = static_cast<int>(i + 1);
		}
	}
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			b[i][j] = static_cast<int>((i + 1) * 10);
		}
	}

	TDynamicMatrix<int> res;
	ASSERT_ANY_THROW(res = a + b);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
	TDynamicMatrix<int> a(4), b(4);
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			a[i][j] = static_cast<int>(i + 1);
			b[i][j] = static_cast<int>((i + 1) * 10);
		}
	}
	TDynamicMatrix<int> res;
	ASSERT_NO_THROW(res = a - b);
	EXPECT_EQ(a.size(), res.size());
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
	TDynamicMatrix<int> a(4), b(5);
	for (size_t i = 0; i < 4; ++i) {
		for (size_t j = 0; j < 4; ++j) {
			a[i][j] = static_cast<int>(i + 1);
		}
	}
	for (size_t i = 0; i < 5; ++i) {
		for (size_t j = 0; j < 5; ++j) {
			b[i][j] = static_cast<int>((i + 1) * 10);
		}
	}

	TDynamicMatrix<int> res;
	ASSERT_ANY_THROW(res = a - b);
}

