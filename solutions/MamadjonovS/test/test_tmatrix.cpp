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
    TDynamicMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
    m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

    TDynamicMatrix<int> m_copy(m);
    ASSERT_TRUE(m == m_copy);

    m_copy[0][0] = 100;
    ASSERT_FALSE(m == m_copy);
    ASSERT_EQ(m[0][0], 1);
    ASSERT_EQ(m_copy[0][0], 100);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(m1);

    m1[0][0] = 100;
    ASSERT_EQ(m2[0][0], 1);

    m2[1][1] = 200;
    ASSERT_EQ(m1[1][1], 4);
}

TEST(TDynamicMatrix, can_get_size)
{
    TDynamicMatrix<int> m(7);
    ASSERT_EQ(m.size(), 7);
}

TEST(TDynamicMatrix, can_set_and_get_element)
{
    TDynamicMatrix<int> m(3);
    m[1][2] = 42;
    ASSERT_EQ(m[1][2], 42);
}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m[-1][0] = 1);
    ASSERT_ANY_THROW(m[0][-1] = 1);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index)
{
    TDynamicMatrix<int> m(3);
    ASSERT_ANY_THROW(m[3][0] = 1);
    ASSERT_ANY_THROW(m[0][3] = 1);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself)
{
    TDynamicMatrix<int> m(2);
    m[0][0] = 1; m[0][1] = 2;
    m[1][0] = 3; m[1][1] = 4;

    ASSERT_NO_THROW(m = m);

    ASSERT_EQ(m[0][0], 1);
    ASSERT_EQ(m[1][1], 4);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(2);
    m2 = m1;

    ASSERT_TRUE(m1 == m2);

    m2[0][0] = 100;
    ASSERT_NE(m1[0][0], 100);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size)
{
    TDynamicMatrix<int> m1(3);
    TDynamicMatrix<int> m2(5);

    m2 = m1;

    ASSERT_EQ(m2.size(), 3);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(4);
    m2 = m1;

    ASSERT_EQ(m2.size(), 2);
    ASSERT_TRUE(m1 == m2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(2);
    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;

    ASSERT_TRUE(m1 == m2);
 
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true)
{
    TDynamicMatrix<int> m(3);
    m[0][0] = 1; m[0][1] = 2; m[0][2] = 3;
    m[1][0] = 4; m[1][1] = 5; m[1][2] = 6;
    m[2][0] = 7; m[2][1] = 8; m[2][2] = 9;

    ASSERT_TRUE(m == m);
   
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    ASSERT_FALSE(m1 == m2);
   
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 1; m1[0][1] = 2;
    m1[1][0] = 3; m1[1][1] = 4;

    TDynamicMatrix<int> m2(2);
    m2[0][0] = 5; m2[0][1] = 6;
    m2[1][0] = 7; m2[1][1] = 8;

    TDynamicMatrix<int> result = m1 + m2;

    ASSERT_EQ(result[0][0], 6);
    ASSERT_EQ(result[0][1], 8);
    ASSERT_EQ(result[1][0], 10);
    ASSERT_EQ(result[1][1], 12);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    ASSERT_ANY_THROW(m1 + m2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size)
{
    TDynamicMatrix<int> m1(2);
    m1[0][0] = 10; m1[0][1] = 20;
    m1[1][0] = 30; m1[1][1] = 40;

    TDynamicMatrix<int> m2(2);
    m2[0][0] = 1; m2[0][1] = 2;
    m2[1][0] = 3; m2[1][1] = 4;

    TDynamicMatrix<int> result = m1 - m2;

    ASSERT_EQ(result[0][0], 9);
    ASSERT_EQ(result[0][1], 18);
    ASSERT_EQ(result[1][0], 27);
    ASSERT_EQ(result[1][1], 36);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size)
{
    TDynamicMatrix<int> m1(2);
    TDynamicMatrix<int> m2(3);

    ASSERT_ANY_THROW(m1 - m2);
}

 