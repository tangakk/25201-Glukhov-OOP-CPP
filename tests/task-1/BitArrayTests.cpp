#include "gtest/gtest.h"
#include "../../task-1/BitArray.h"
#include <iostream>

using namespace std;

TEST(BitArrayTests, test0) {
    BitArray a;
}

TEST(BitArrayTests, test1) {
    BitArray a(10, 0b1010101010);
    cout << a.to_string() << endl;
    for (int i = 0; i < 10; ++i) {
        ASSERT_EQ(a[i], (i % 2 != 0));
    }
}

TEST(BitArrayTests, test2) {
    BitArray a(5, 0b11111);
    ASSERT_EQ(a[2], true);
    a.reset(2);
    ASSERT_EQ(a[2], false);
    a.set(2);
    ASSERT_EQ(a[2], true);
    a.set();
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(a[i], true);
    }
    a.reset();
    for (int i = 0; i < 5; ++i) {
        ASSERT_EQ(a[i], false);
    }
}

TEST(BitArrayTests, test3) {
    BitArray a(5, 0b11111);
    BitArray b(5, 0b00000);
    ASSERT_NE(a, b);
    b = a;
    ASSERT_EQ(a, b);
    BitArray c(a);
    ASSERT_EQ(a, c);
}

TEST(BitArrayTests, test4) {
    BitArray a(-1, 0b11111);
    ASSERT_EQ(a.size(), 0);
    ASSERT_EQ(a.empty(), true);
}

TEST(BitArrayTests, test5) {
    BitArray a(5, 0b10101);
    BitArray b(5, 0b11000);
    ASSERT_EQ(a.to_string(), "10101");
    a &= b;
    ASSERT_EQ(a.to_string(), "00001");
    a |= b;
    ASSERT_EQ(a.to_string(), "00011");
    a ^= b;
    ASSERT_EQ(a.to_string(), "00000");
    b = ~b;
    ASSERT_EQ(b.to_string(), "11100");
}

TEST(BitArrayTests, test6) {
    BitArray a(5, 0b10101);
    a <<= 2;
    ASSERT_EQ(a.to_string(), "10100");
    a >>= 2;
    ASSERT_EQ(a.to_string(), "00101");
    BitArray b(16, 0b0001'1010'0110'1111);
    a = b << 10;
    ASSERT_EQ(a.to_string(), "1011110000000000");
    a = b >> 10;
    ASSERT_EQ(a.to_string(), "0000000000000110");
}

TEST(BitArrayTests, test7) {
    BitArray a(5, 0b11111);
    ASSERT_EQ(a.any(), true);
    ASSERT_EQ(a.all(), false);
    ASSERT_EQ(a.none(), false);
    ASSERT_EQ(a.count(), 3);
    a.reset();
    ASSERT_EQ(a.any(), false);
    ASSERT_EQ(a.all(), false);
    ASSERT_EQ(a.none(), true);
}

TEST(BitArrayTests, test8) {
    BitArray a(5, 0b11111);
    BitArray b(5, 0b00000);
    a.swap(b);
    ASSERT_EQ(a.to_string(), "00000");
    ASSERT_EQ(b.to_string(), "11111");
}

TEST(BitArrayTests, test9) {
    BitArray a(5, 0b10101);
    a.push_back(true);
    ASSERT_EQ(a.size(), 6);
    ASSERT_EQ(a[5], true);
    a.push_back(false);
    ASSERT_EQ(a.size(), 7);
    ASSERT_EQ(a[6], false);
    a.clear();
    ASSERT_EQ(a.size(), 0);
}

TEST(BitArrayTests, test10) {
    BitArray a(5, 0b10000);
    BitArray b(10, 0b0011000000);
    a |= b;
    ASSERT_EQ(a.size(), 5);
    ASSERT_EQ(a.to_string(), "10110");
    ASSERT_ANY_THROW(a&=b);
}

TEST(BitArrayTests, resizeTest) {
    BitArray a(5, 0b00000);
    a.resize(10, true);
    ASSERT_EQ(a.size(), 10);
    ASSERT_EQ(a.to_string(), "0000011111");
    ASSERT_ANY_THROW(a.resize(5));
    a.clear();
    a.resize(10, false);
    ASSERT_EQ(a.size(), 3);
    ASSERT_EQ(a.to_string(), "111");
}

TEST(BitArrayTests, operatorTest) {
    BitArray a(5, 0b11111);
    a[3] = 0;
    ASSERT_EQ(a.to_string(), "11101");
}
