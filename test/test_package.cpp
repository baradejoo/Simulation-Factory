//
// Created by Bartolemello on 15.12.2019.
//
#include "gtest/gtest.h"
#include "package.hpp"
#include "nodes.hpp"
#include "storage_types.hpp"

TEST(FabrykaPackageTest, CreationTest) {
    Package p1;
    Package p2;
    Package p3;
    Package p4;
    EXPECT_EQ(p1.get_id(), 1);
    EXPECT_EQ(p2.get_id(), 2);
    EXPECT_EQ(p3.get_id(), 3);
    EXPECT_EQ(p4.get_id(), 4);
}


TEST(FabrykaPackageQueueTest, PopQueFIFO){
    PackageQueue Que_FIFO(PackageQueueType::FIFO);
    Que_FIFO.push(Package());
    Que_FIFO.push(Package());
    Que_FIFO.push(Package());

    Package p1 = Que_FIFO.pop();
    Package p2 = Que_FIFO.pop();

    ASSERT_EQ(p1.get_id(),1);
    ASSERT_EQ(p2.get_id(),2);
}

TEST(FabrykaPackageQueueTest, PopQueLIFO){
    PackageQueue Que_LIFO(PackageQueueType::LIFO);
    Que_LIFO.push(Package());
    Que_LIFO.push(Package());
    Que_LIFO.push(Package());

    Package p1 = Que_LIFO.pop();
    Package p2 = Que_LIFO.pop();

    ASSERT_EQ(p1.get_id(),3);
    ASSERT_EQ(p2.get_id(),2);
}