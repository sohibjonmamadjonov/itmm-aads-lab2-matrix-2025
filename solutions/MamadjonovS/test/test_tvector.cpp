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
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    TDynamicVector<int> v_copy(v);

    ASSERT_TRUE(v == v_copy);

    v_copy[0] = 100;
    ASSERT_FALSE(v == v_copy);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v_copy[0], 100);
}

TEST(TDynamicVector, copied_vector_has_its_own_memory)
{
    TDynamicVector<int> v1(2);
    v1[0] = 1; v1[1] = 2;

    TDynamicVector<int> v2(v1);

    v1[0] = 100;
    ASSERT_EQ(v2[0], 1);

    v2[1] = 200;
    ASSERT_EQ(v1[1], 2);
}

TEST(TDynamicVector, can_get_size)
{
    TDynamicVector<int> v(4);
    EXPECT_EQ(4, v.size());
}

TEST(TDynamicVector, can_set_and_get_element)
{
    TDynamicVector<int> v(4);
    v[0] = 4;
    EXPECT_EQ(4, v[0]);
}

TEST(TDynamicVector, throws_when_set_element_with_negative_index)
{
    TDynamicVector<int> v(3);
    ASSERT_ANY_THROW(v[-1] = 1);
    ASSERT_ANY_THROW(v.at(-1) = 1);
}

TEST(TDynamicVector, throws_when_set_element_with_too_large_index)
{
    TDynamicVector<int> v(3);
    ASSERT_ANY_THROW(v[3] = 1);
    ASSERT_ANY_THROW(v.at(3) = 1);
}

TEST(TDynamicVector, can_assign_vector_to_itself)
{
    TDynamicVector<int> v(2);
    v[0] = 1; v[1] = 2;

    ASSERT_NO_THROW(v = v);

    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[1], 2);
}

TEST(TDynamicVector, can_assign_vectors_of_equal_size)
{
    TDynamicVector<int> v1(2);
    v1[0] = 1; v1[1] = 2;

    TDynamicVector<int> v2(2);
    v2 = v1;

    ASSERT_TRUE(v1 == v2);

    v2[0] = 100;
    ASSERT_NE(v1[0], 100);
}

TEST(TDynamicVector, assign_operator_change_vector_size)
{
    TDynamicVector<int> v1(3);
    TDynamicVector<int> v2(5);

    v2 = v1;

    ASSERT_EQ(v2.size(), 3);
}

TEST(TDynamicVector, can_assign_vectors_of_different_size)
{
    TDynamicVector<int> v1(2);
    v1[0] = 1; v1[1] = 2;

    TDynamicVector<int> v2(4);
    v2 = v1;

    ASSERT_EQ(v2.size(), 2);
    ASSERT_TRUE(v1 == v2);
}

TEST(TDynamicVector, compare_equal_vectors_return_true)
{
    TDynamicVector<int> v1(2);
    v1[0] = 1; v1[1] = 2;

    TDynamicVector<int> v2(2);
    v2[0] = 1; v2[1] = 2;

    ASSERT_TRUE(v1 == v2);
    ASSERT_FALSE(v1 != v2);
}

TEST(TDynamicVector, compare_vector_with_itself_return_true)
{
    TDynamicVector<int> v(3);
    v[0] = 1; v[1] = 2; v[2] = 3;

    ASSERT_TRUE(v == v);
    ASSERT_FALSE(v != v);
}

TEST(TDynamicVector, vectors_with_different_size_are_not_equal)
{
    TDynamicVector<int> v1(2);
    TDynamicVector<int> v2(3);

    ASSERT_FALSE(v1 == v2);
    ASSERT_TRUE(v1 != v2);
}

TEST(TDynamicVector, can_add_scalar_to_vector)
{
    TDynamicVector<int> v(2);
    v[0] = 1; v[1] = 2;

    TDynamicVector<int> result = v + 3;

    ASSERT_EQ(result[0], 4);
    ASSERT_EQ(result[1], 5);
}

TEST(TDynamicVector, can_subtract_scalar_from_vector)
{
    TDynamicVector<int> v(2);
    v[0] = 5; v[1] = 6;

    TDynamicVector<int> result = v - 2;

    ASSERT_EQ(result[0], 3);
    ASSERT_EQ(result[1], 4);
}

TEST(TDynamicVector, can_multiply_scalar_by_vector)
{
    TDynamicVector<int> v(2);
    v[0] = 1; v[1] = 2;

    TDynamicVector<int> result = v * 3;

    ASSERT_EQ(result[0], 3);
    ASSERT_EQ(result[1], 6);
}

TEST(TDynamicVector, can_add_vectors_with_equal_size)
{
    TDynamicVector<int> v1(2);
    v1[0] = 1; v1[1] = 2;

    TDynamicVector<int> v2(2);
    v2[0] = 3; v2[1] = 4;

    TDynamicVector<int> result = v1 + v2;

    ASSERT_EQ(result[0], 4);
    ASSERT_EQ(result[1], 6);
}

TEST(TDynamicVector, cant_add_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(2);
    TDynamicVector<int> v2(3);

    ASSERT_ANY_THROW(v1 + v2);
}

TEST(TDynamicVector, can_subtract_vectors_with_equal_size)
{
    TDynamicVector<int> v1(2);
    v1[0] = 5; v1[1] = 6;

    TDynamicVector<int> v2(2);
    v2[0] = 1; v2[1] = 2;

    TDynamicVector<int> result = v1 - v2;

    ASSERT_EQ(result[0], 4);
    ASSERT_EQ(result[1], 4);
}

TEST(TDynamicVector, cant_subtract_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(2);
    TDynamicVector<int> v2(3);

    ASSERT_ANY_THROW(v1 - v2);
}

TEST(TDynamicVector, can_multiply_vectors_with_equal_size)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    TDynamicVector<int> v2(3);
    v2[0] = 4; v2[1] = 5; v2[2] = 6;

    int result = v1 * v2; // Скалярное произведение

    ASSERT_EQ(result, 32); // 1*4 + 2*5 + 3*6 = 4 + 10 + 18 = 32
}

TEST(TDynamicVector, cant_multiply_vectors_with_not_equal_size)
{
    TDynamicVector<int> v1(2);
    TDynamicVector<int> v2(3);

    ASSERT_ANY_THROW(v1 * v2);
}

// Дополнительные тесты для полноты покрытия
TEST(TDynamicVector, can_use_at_method_with_const_object)
{
    const TDynamicVector<int> v(3);
    ASSERT_NO_THROW(v.at(0));
    ASSERT_ANY_THROW(v.at(3));
}

TEST(TDynamicVector, can_swap_vectors)
{
    TDynamicVector<int> v1(2);
    v1[0] = 1; v1[1] = 2;

    TDynamicVector<int> v2(2);
    v2[0] = 3; v2[1] = 4;

    swap(v1, v2);

    ASSERT_EQ(v1[0], 3);
    ASSERT_EQ(v1[1], 4);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
}

TEST(TDynamicVector, can_create_vector_from_array)
{
    int arr[] = { 1, 2, 3, 4, 5 };
    ASSERT_NO_THROW(TDynamicVector<int> v(arr, 5));

    TDynamicVector<int> v(arr, 5);
    ASSERT_EQ(v.size(), 5);
    ASSERT_EQ(v[0], 1);
    ASSERT_EQ(v[4], 5);
}

TEST(TDynamicVector, can_use_move_constructor)
{
    TDynamicVector<int> v1(3);
    v1[0] = 1; v1[1] = 2; v1[2] = 3;

    ASSERT_NO_THROW(TDynamicVector<int> v2(std::move(v1)));

    TDynamicVector<int> v2(std::move(v1));
    ASSERT_EQ(v2.size(), 3);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[2], 3);
    ASSERT_EQ(v1.size(), 0); // После перемещения размер должен быть 0
}

TEST(TDynamicVector, can_use_move_assignment)
{
    TDynamicVector<int> v1(2);
    v1[0] = 1; v1[1] = 2;

    TDynamicVector<int> v2(3);
    v2 = std::move(v1);

    ASSERT_EQ(v2.size(), 2);
    ASSERT_EQ(v2[0], 1);
    ASSERT_EQ(v2[1], 2);
    ASSERT_EQ(v1.size(), 0); // После перемещения размер должен быть 0
}