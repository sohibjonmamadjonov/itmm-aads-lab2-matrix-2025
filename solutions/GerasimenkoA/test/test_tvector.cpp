#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicVector, can_create_vector_with_positive_length)
{
  ASSERT_NO_THROW(TDynamicVector<int> v(5));
}

TEST(TDynamicVector, cant_create_too_large_vector)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(MAX_VECTOR_SIZE + 1));
}

TEST(TDynamicVector, throws_when_create_vector_with_negative_length)
{
  ASSERT_ANY_THROW(TDynamicVector<int> v(-5));
}

TEST(TDynamicVector, can_create_copied_vector)
{
  TDynamicVector<int> v(10);

  ASSERT_NO_THROW(TDynamicVector<int> v1(v));
}

TEST(TDynamicVector, copied_vector_is_equal_to_source_one)
{
	TDynamicVector<int> a(10), b(10);
	for (size_t i = 0; i < 10; ++i) {
		a[i] = 1;
		b[i] = 2;
	}
	a = b;
	EXPECT_EQ(a, b);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
	TDynamicVector<int> a(4);
	for (size_t i = 0; i < 4; ++i) 
		a[i] = static_cast<int>(i + 1);

	TDynamicVector<int> b(a);
	b[0] = 100;

	ASSERT_EQ(1, a[0]);
	ASSERT_EQ(100, b[0]);
	ASSERT_FALSE(a == b);
}

TEST(TDynamicVector, can_get_size)
{
	TDynamicVector<int> v(4);

  EXPECT_EQ(4, v.size());
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
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(-1));
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
	TDynamicVector<int> v(4);
	ASSERT_ANY_THROW(v.at(5));
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 3; v[2] = 4; v[3] = 6;
	v = v;
	EXPECT_EQ(1, v[0]);
	EXPECT_EQ(3, v[1]);
	EXPECT_EQ(4, v[2]);
	EXPECT_EQ(6, v[3]);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
	TDynamicVector<int> a(4), b(4);
	ASSERT_NO_THROW(a = b);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
	TDynamicVector<int> a(3), b(4);
	a = b;
	EXPECT_EQ(b.size(), a.size());
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
	TDynamicVector<int> a(3), b(4);
	ASSERT_NO_THROW(a = b);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
	TDynamicVector<int> v(4), b(4);
	v[0] = 1; v[1] = 3; v[2] = 4; v[3] = 6;
	b[0] = 1; b[1] = 3; b[2] = 4; b[3] = 6;
	ASSERT_TRUE(v == b);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
	TDynamicVector<int> v(4);
	v[0] = 1; v[1] = 3; v[2] = 4; v[3] = 6;
	ASSERT_TRUE(v == v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
	TDynamicVector<int> a(3), b(4);
	ASSERT_FALSE(a == b);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
	TDynamicVector<int> a(4);
	int c = 6;
	for (size_t i = 0; i < 4; ++i)
		a[i] = static_cast<int>(i + 1);

	TDynamicVector<int> res = a + c;
	EXPECT_EQ(c + a[0], res[0]);
	EXPECT_EQ(c + a[1], res[1]);
	EXPECT_EQ(c + a[2], res[2]);
	EXPECT_EQ(c + a[3], res[3]);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
	TDynamicVector<int> a(4);
	int c = 6;
	for (size_t i = 0; i < 4; ++i)
		a[i] = static_cast<int>(i + 1);

	TDynamicVector<int> res = a - c;
	EXPECT_EQ(a[0] - c, res[0]);
	EXPECT_EQ(a[1] - c, res[1]);
	EXPECT_EQ(a[2] - c, res[2]);
	EXPECT_EQ(a[3] - c, res[3]);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
	TDynamicVector<int> a(4);
	int c = 6;
	for (size_t i = 0; i < 4; ++i)
		a[i] = static_cast<int>(i + 1);

	TDynamicVector<int> res = a * c;
	EXPECT_EQ(c * a[0], res[0]);
	EXPECT_EQ(c * a[1], res[1]);
	EXPECT_EQ(c * a[2], res[2]);
	EXPECT_EQ(c * a[3], res[3]);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
	TDynamicVector<int> a(4), b(4);
	for (size_t i = 0; i < 4; ++i) {
		a[i] = static_cast<int>(i + 1);
		b[i] = static_cast<int>((i + 1) * 10);
	}	
	TDynamicVector<int> res;
	ASSERT_NO_THROW(res = a + b);
	EXPECT_EQ(a.size(), res.size());
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(4), b(5);
	for (size_t i = 0; i < 4; ++i) a[i] = static_cast<int>(i + 1);
	for (size_t i = 0; i < 5; ++i) b[i] = static_cast<int>((i + 1) * 10);
	TDynamicVector<int> res;
	ASSERT_ANY_THROW(res = a + b);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
	TDynamicVector<int> a(4), b(4);
	for (size_t i = 0; i < 4; ++i) {
		a[i] = static_cast<int>(i + 1);
		b[i] = static_cast<int>((i + 1) * 10);
	}
	TDynamicVector<int> res;
	ASSERT_NO_THROW(res = a - b);
	EXPECT_EQ(a.size(), res.size());
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
	TDynamicVector<int> a(4), b(5);
	for (size_t i = 0; i < 4; ++i) a[i] = static_cast<int>(i + 1);
	for (size_t i = 0; i < 5; ++i) b[i] = static_cast<int>((i + 1) * 10);
	TDynamicVector<int> res;
	ASSERT_ANY_THROW(res = a - b);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
	ADD_FAILURE(); //noexcept
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
	ADD_FAILURE(); //noexcept
}

