//
// Created by Xiaodong Liu on 8/21/22.
//

#include "CustomVector.h"
#include "gtest/gtest.h"

namespace ns{
    class CustomVectorTest: public ::testing::Test{
    protected:
        void SetUp() {
            B = vector<int>(5,1);
            C = vector<int>{1,2,3,4,5};
        }
        vector<int> A, B, C;
    };

    TEST_F(CustomVectorTest, DefaultConstructor){
        EXPECT_EQ(A.size(), 0);
        EXPECT_EQ(A.capacity(), 1);
    }

    TEST_F(CustomVectorTest, RangeConstructor){
        vector<int> D(C.begin(), C.end());
        ASSERT_EQ(D.size(), 5);
        EXPECT_EQ(D[0], 1);
        EXPECT_EQ(D[1], 2);
        EXPECT_EQ(D[2], 3);
        EXPECT_EQ(D[3], 4);
        EXPECT_EQ(D[4], 5);
    }

    TEST_F(CustomVectorTest, MoveConstructor){
        vector<int> D(C);
        vector<int> E(move(C));
        EXPECT_THROW({int val = C[0];}, out_of_range);
        for(int i = 0; i < D.size(); ++i){
            EXPECT_EQ(E[i], D[i]);
        }
    }

    TEST_F(CustomVectorTest, Reserve){
        EXPECT_EQ(B.capacity(), 8);
        B.reserve(100);
        EXPECT_EQ(B.capacity(), 100);
        EXPECT_EQ(B.size(), 5);
        B.reserve(80);
        EXPECT_EQ(B.capacity(), 80);
        EXPECT_EQ(B.size(), 5);
        B.reserve(3);
        EXPECT_EQ(B.capacity(), 80);
        EXPECT_EQ(B.size(), 5);
        B.reserve(5);
        EXPECT_EQ(B.capacity(), 5);
        EXPECT_EQ(B.size(), 5);
    }

    TEST_F(CustomVectorTest, Resize){
        B.resize(10);
        EXPECT_EQ(B.size(), 10);
        for(int i = 0; i < 5; ++i){
            EXPECT_EQ(B[i], 1);
        }
        for(int i = 5; i < 10; ++i){
            EXPECT_EQ(B[i], 0);
        }
        B.resize(20, 2);
        for(int i = 0; i < 5; ++i){
            EXPECT_EQ(B[i], 1);
        }
        for(int i = 5; i < 10; ++i){
            EXPECT_EQ(B[i], 0);
        }
        for(int i = 10; i < 20; ++i){
            EXPECT_EQ(B[i], 2);
        }
        B.resize(3);
        EXPECT_EQ(B.size(), 3);
        for(int i = 0; i < 3; ++i){
            EXPECT_EQ(B[i], 1);
        }
        B.resize(2, 0);
        EXPECT_EQ(B[0], 1);
        EXPECT_EQ(B[1], 1);
        B.resize(2);
        EXPECT_EQ(B.size(), 2);
        EXPECT_EQ(B[0], 1);
        EXPECT_EQ(B[1], 1);
        B.resize(2, 100);
        EXPECT_EQ(B.size(), 2);
        EXPECT_EQ(B[0], 1);
        EXPECT_EQ(B[1], 1);
    }

    TEST_F(CustomVectorTest, PopBack){
        C.pop_back();
        EXPECT_EQ(C.size(), 4);
        EXPECT_THROW({int val = C[4];}, out_of_range);
        EXPECT_EQ(C[3], 4);
        while(C.size() > 0){
            C.pop_back();
        }
        EXPECT_EQ(C.size(), 0);
        C.pop_back();
        EXPECT_EQ(C.size(), 0);
    }

    TEST_F(CustomVectorTest, PushBack){
        for(int i = 0; i < 20; ++i)  {
            A.push_back(0);
            EXPECT_EQ(A[i], 0);
            EXPECT_EQ(A.size(), i+1);
        }
    }

    TEST_F(CustomVectorTest, IteratorAssignmentOperator){
        vector<int>::iterator it = A.begin();
        EXPECT_EQ(it, A.end());
        it = B.begin();
        auto endIt = B.end();
        while(it != endIt){
            EXPECT_EQ(*it, 1);
            ++it;
        }
        it = C.begin();
        EXPECT_EQ(*it++, 1);
        EXPECT_EQ(*it++, 2);
        EXPECT_EQ(*it++, 3);
        EXPECT_EQ(*it++, 4);
        EXPECT_EQ(*it++, 5);
    }
}