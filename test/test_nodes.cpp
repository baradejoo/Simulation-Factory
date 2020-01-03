//
// Created by Bartek on 2020-01-03.
//

#include "gtest/gtest.h"
#include "package.hpp"
#include "nodes.hpp"
#include "storage_types.hpp"


TEST(FabrykaStorehouseTest, CreationTest) {
    // Uwaga: zakładam w tym teście że magazyn używa kolejki typu LIFO!

    //stworzenie wskaźnika na interfejs kolejki
    auto que_store_ptr = std::make_unique<PackageQueue>(PackageQueueType::LIFO);

    //umieszczenie produktów w storehouse
    que_store_ptr->push(Package());
    que_store_ptr->push(Package());
    que_store_ptr->push(Package());

    // przypisanie StoreHouse wsk. na interfejs oraz identyfkatora
    auto store = Storehouse(4,std::move(que_store_ptr));


    ASSERT_EQ((*store.begin()).get_id(), 1);
    ASSERT_EQ((*store.end()).get_id(), 3);

}