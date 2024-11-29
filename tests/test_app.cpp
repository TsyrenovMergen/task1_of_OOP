#include <gtest/gtest.h>
#include "C:\Users\tsire\source\repos\googletest1\lib\OOP1.hpp"

TEST(Constructor, Default_constructor)
{
	BitArray a;
	EXPECT_EQ(a.to_string()=="", 1);
	EXPECT_EQ(a.size(), 0);
	EXPECT_EQ(a.empty(), 1);
	EXPECT_EQ(a.count(), 0);
}

TEST(Constructor, Copying_constructor)
{
	BitArray b;
	b.push_back(true);
	b.push_back(false);
	BitArray a(b);
	EXPECT_EQ(a==b, 1);
	EXPECT_EQ(a.to_string().compare(b.to_string()), 1);
	EXPECT_EQ(a.size() == b.size(), 1);
}

TEST(Constructor, Numberbits_constructor)
{
	BitArray c(64, 0b11110000111000101010100100011000);
	EXPECT_EQ(c.to_string().compare("1111000011100010101010010001100000000000000000000000000000000000"), 1);
	EXPECT_EQ(c.size() == 64, 1);
}

TEST(Swap, swap)
{
	BitArray a(40, 0b11011011101010011011101001010001);
	BitArray t(32, 0b11011011101010011011101001011111);
	a.swap(t);
	EXPECT_EQ(a.size(), 32);
	EXPECT_EQ(t.size(), 40);
	EXPECT_EQ(a.to_string().compare("11011011101010011011101001011111"), 1);
	EXPECT_EQ(t.to_string().compare("1101101110101001101110100101000100000000"), 1);
}

TEST(Operator_assignment, operator_assigment)
{
	BitArray a(40, 0b11011011101010011011101001010001);
	BitArray b;
	EXPECT_EQ(a != b, 1);
	b = a;
	EXPECT_EQ(a == b, 1);
}

TEST(Resize, resize) 
{
	BitArray a;
	a.resize(64, true);
	EXPECT_EQ(a.to_string().compare("1111111111111111111111111111111111111111111111111111111111111111"), 1);
	a.resize(0, true);
	EXPECT_EQ(a.to_string().compare(""), 0);
	a.resize(10, true);
	EXPECT_EQ(a.to_string().compare("1111111111000000000000000000000000000000000000000000000000000000"), 1);
	a.resize(0);
	a.resize(10, false);
	EXPECT_EQ(a.to_string().compare("0000000000000000000000000000000000000000000000000000000000000000"), 1);
}

TEST(Clear, clear)
{
	BitArray a;
	EXPECT_EQ(a.size(), 0);
	a.push_back(true);
	EXPECT_EQ(a.size(), 1);
	a.clear();
	EXPECT_EQ(a.size(), 0);
	EXPECT_EQ(a.empty(), 1);
}

TEST(Push_back, push_back) 
{
	BitArray a;
	a.push_back(true);
	EXPECT_EQ(a[0], 1);
	a.push_back(false);
	EXPECT_EQ(a[1], 0);
	a.resize(32, true);
	a.push_back(false);
	EXPECT_EQ(a[32], false);
}

TEST(Operator_as_con_as_dis_as_inv, Operator_as_con)
{
	BitArray t(32, 0b11011011101010011011101001010001);
	BitArray s(32, 0b10011011011001001011011101010011);
	t &= s;
	EXPECT_EQ(t.to_string().compare("10011011001000001011001001010001"), 1);
}

TEST(Operator_as_con_as_dis_as_inv, Operator_as_dis)
{
	BitArray t(32, 0b11011011101010011011101001010001);
	BitArray s(32, 0b10011011011001001011011101010011);
	t |= s;
	EXPECT_EQ(t.to_string().compare("11011011111011011011111101010011"), 1);
}

TEST(Operator_as_con_as_dis_as_inv, Operator_as_inv)
{
	BitArray t(32, 0b11011011101010011011101001010001);
	BitArray s(32, 0b10011011011001001011011101010011);
	t ^= s;
	EXPECT_EQ(t.to_string().compare("01000000110011010000110100000010"), 1);
}

TEST(Set_and_Reset, Set)
{
	BitArray b;
	b.resize(32, false);
	b.set();
	EXPECT_EQ(b.count(), 32);
}

TEST(Set_and_Reset, Reset)
{
	BitArray b;
	b.resize(32, false);
	b.reset();
	EXPECT_EQ(b.count(), 0);
}

TEST(Set_and_Reset, Set_n)
{
	BitArray b;
	b.resize(32, false);
	b.set(3, true);
	EXPECT_EQ(b[3], true);
	b.set();
	b.set(6, false);
	EXPECT_EQ(b[6], 0);
}

TEST(Set_and_Reset, Reset_n)
{
	BitArray b;
	b.resize(32, true);
	b.reset(6);
	EXPECT_EQ(b[6], 0);
}

TEST(ShiftOperations, ShiftLeftas)
{
	BitArray b(32, 0b11110000111000101010000000000000);
	b <<= 4;
	EXPECT_EQ(b.to_string().compare("00001110001010100000000000000000"), 1);
}

TEST(ShiftOperations, ShiftRigthas)
{
	BitArray b(32, 0b11110000111000101010000000000000);
	b >>= 4;
	EXPECT_EQ(b.to_string().compare("00001111000011100010101000000000"), 1);
}

TEST(ShiftOperations, ShiftLeft)
{
	BitArray b(32, 0b11110000111000101010000000000000);
	BitArray a;
	a = b << 4;
	EXPECT_EQ(a.to_string().compare("00001110001010100000000000000000"), 1);
}

TEST(ShiftOperations, ShiftRigth)
{
	BitArray b(32, 0b11110000111000101010000000000000);
	BitArray a;
	a = b >> 4;
	EXPECT_EQ(b.to_string().compare("00001111000011100010101000000000"), 1);
}

TEST(Any_None, Any)
{
	BitArray a;
	a.push_back(false);
	EXPECT_EQ(a.any(), 0);
	a.push_back(true);
	EXPECT_EQ(a.any(), 1);
	a.resize(33, false);
	a.reset(1);
	a.set(32, true);
	EXPECT_EQ(a.any(), 1);
}

TEST(Any_None, None)
{
	BitArray a;
	a.push_back(false);
	EXPECT_EQ(a.none(), 1);
	a.push_back(true);
	EXPECT_EQ(a.any(), 0);
	a.resize(33, false);
	a.reset(1);
	EXPECT_EQ(a.none(), 1);
}

TEST(Count, count)
{
	BitArray b;
	EXPECT_EQ(b.count(), 0);
	b.push_back(true);
	EXPECT_EQ(b.count(), 1);
	b.push_back(false);
	EXPECT_EQ(b.count(), 1);
	b.set();
	EXPECT_EQ(b.count(), 2);
	b.reset();
	EXPECT_EQ(b.count(), 0);
}

TEST(Opeator_index, operator_index)
{
	BitArray b(48, 0b11110000111000101010100100011001);
	EXPECT_EQ(b[0], 1);
	EXPECT_EQ(b[4], 0);
	EXPECT_EQ(b[8], 1);
	EXPECT_EQ(b[32], 0);
}

TEST(Size, size)
{
	BitArray b;
	EXPECT_EQ(b.size(), 0);
	b.push_back(true);
	EXPECT_EQ(b.size(), 1);
	b.resize(13, true);
	EXPECT_EQ(b.size(), 13);
	b.clear();
	EXPECT_EQ(b.size(), 0);
}

TEST(Empty, empty)
{
	BitArray b;
	EXPECT_EQ(b.empty(), 1);
	b.push_back(true);
	EXPECT_EQ(b.empty(), 0);
	b.clear();
	EXPECT_EQ(b.empty(), 1);
}

TEST(To_string, to_string)
{
	BitArray a(40, 0b11011011101010011011101001010001);
	a.set(34, true);
	a.set(37, true);
	EXPECT_EQ(a.to_string().compare("1101101110101001101110100101000100100100"), 1);
}

TEST(Operators_eq_neq, Operator_eq)
{
	BitArray z(32, 0);
	z.set();
	BitArray y(32, 0);
	y.set();
	EXPECT_EQ(z == y, 1);
	y.push_back(false);
	EXPECT_EQ(z == y, 0);
	y.resize(31, 0);
	EXPECT_EQ(z == y, 0);
}

TEST(Operators_eq_neq, Operator_neq)
{
	BitArray x(32, 0);
	x.set();
	BitArray u(32, 0);
	u.set();
	EXPECT_EQ(x != u, 0);
	u.push_back(false);
	EXPECT_EQ(x !=u, 1);
	u.resize(31, 0);
	EXPECT_EQ(x == u, 1);
}

TEST(Operators_con_dis_inv, Opeator_con)
{
	BitArray t(32, 0b11011011101010011011101001010001);
	BitArray s(32, 0b10011011011001001011011101010011);
	BitArray v;
	v = t & s;
	EXPECT_EQ(v.to_string().compare("10011011001000001011001001010001"), 1);
}

TEST(Operator_con_dis_inv, Operator_dis)
{
	BitArray t(32, 0b11011011101010011011101001010001);
	BitArray s(32, 0b10011011011001001011011101010011);
	BitArray v;
	v = t | s;
	EXPECT_EQ(v.to_string().compare("11011011111011011011111101010011"), 1);
}

TEST(Operator_con_dis_inv, Operator_inv)
{
	BitArray t(32, 0b11011011101010011011101001010001);
	BitArray s(32, 0b10011011011001001011011101010011);
	BitArray v;
	v = t ^ s;
	EXPECT_EQ(v.to_string().compare("01000000110011010000110100000010"), 1);
}