//
// Created by Bartolemello on 15.12.2019.
//
#include "gtest/gtest.h"
#include "package.hpp"

TEST(FabrykaPackageTest, creationTest) {
    Package p1;
    Package p2;
    Package p3;
    Package p4;
    EXPECT_EQ(p1.get_id(), 1);
    EXPECT_EQ(p2.get_id(), 2);
    EXPECT_EQ(p3.get_id(), 3);
    EXPECT_EQ(p4.get_id(), 4);
}

TEST(FabrykaPackageTest, deletingTest) {
    Package p1;
    Package p2;
    Package p3;
    Package p4;

    p1.~Package();

    EXPECT_EQ(p2.get_id(), 2);
    EXPECT_EQ(p3.get_id(), 3);
    EXPECT_EQ(p4.get_id(), 4);

    Package p5;
    EXPECT_EQ(p5.get_id(), 1);
    EXPECT_EQ(p2.get_id(), 2);
    EXPECT_EQ(p3.get_id(), 3);
    EXPECT_EQ(p4.get_id(), 4);
}

//TEST(FabrykaPackageTest, moveOperationTest) {
//    Package p1;
//    Package p2;
//    p2 = Package(p1);
//}