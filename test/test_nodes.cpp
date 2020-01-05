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

TEST(PackageSenderTest, EmptyBufferTest) { //wysyłanie półproduktu: czy po wysłaniu bufor jest pusty?
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    r1.preferences_list_.add_receiver(&w1);

    r1.deliver_goods(0);
    r1.send_package();

    EXPECT_EQ(std::nullopt, r1.get_sending_buffer());
}

TEST(RampTest, DeliveryTest) { //dostawa: czy dostawa odbywa się we właściwej turze? czy półprodukt trafia od razu do bufora?
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    r2.preferences_list_.add_receiver(&w1);
    r2.deliver_goods(0);
    r2.send_package();
    r2.deliver_goods(1);
    r2.send_package();
    r2.deliver_goods(2);

    EXPECT_EQ(1, r2.get_sending_buffer().has_value());
}

TEST(RampTest, NotDeliveryTest) { //dostawa: czy dostawa odbywa się we właściwej turze? czy półprodukt trafia od razu do bufora?
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    r2.preferences_list_.add_receiver(&w1);
    r2.deliver_goods(0);
    r2.send_package();
    r2.deliver_goods(1);

    EXPECT_EQ(0, r2.get_sending_buffer().has_value());
}

TEST(StorehouseTest, CorrectReceivingTest) {
    PackageQueue q(PackageQueueType::FIFO);
    std::unique_ptr<IPackageStockpile> ptr = std::make_unique<PackageQueue>(q);
    Storehouse s(1, std::move(ptr));
    Ramp r(1,2);
    r.preferences_list_.add_receiver(&s);
    r.deliver_goods(0);
    r.send_package();
    r.deliver_goods(1);
    r.send_package();
    r.deliver_goods(2);
    r.send_package();
    EXPECT_EQ(2, s.cend()->get_id());
}

TEST(ReceiverPreferencesTest, CorectReceiver) {
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::LIFO);
    PackageQueue q3(PackageQueueType::FIFO);
    PackageQueue q4(PackageQueueType::LIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageQueue> ptr2 = std::make_unique<PackageQueue>(q2);
    std::unique_ptr<IPackageStockpile> ptr3 = std::make_unique<PackageQueue>(q3);
    std::unique_ptr<IPackageStockpile> ptr4 = std::make_unique<PackageQueue>(q4);
    Storehouse s1(1, std::move(ptr3));
    Storehouse s2(2, std::move(ptr4));
    Ramp r1(1, 1);
    Ramp r2(2, 2);
    Worker w1(1, 1, std::move(ptr1));
    Worker w2(2, 2, std::move(ptr2));

    std::function<double(void)> rng = // funckja losujaca;
    ReceiverPreferences pref(rng);

    IPackageReceiver* rec;

    rec = &w1;

    pref.add_receiver(&w1);
    pref.add_receiver(&w2);
    pref.add_receiver(&s1);
    // test logic

    EXPECT_EQ(rec, pref.choose_receiver());
}
/*
TEST(ReceiverPreferences, ProbabilityScalingTest) {
    std::function<double(void)> rng = your_num;
    ReceiverPreferences pref(rng);
    IPackageReceiver* r1;
    IPackageReceiver* r2;
    pref.add_receiver(r1);
    pref.add_receiver(r2);
    EXPECT_EQ(0.5, pref.get_probability(r1));
}
*/
TEST(WorkerBuffer, PackageReceivedInBuffer) {
    PackageQueue q(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q);
    std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(q);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.preferences_list_.add_receiver(&w);
    w.preferences_list_.add_receiver(&s);
    r.deliver_goods(0);
    r.send_package();
    w.do_work(0);
    w.send_package();
    r.deliver_goods(1);
    r.send_package();
    w.do_work(1);
    w.send_package();
    r.deliver_goods(2);
    r.send_package();
    w.do_work(2);
    w.send_package();
    EXPECT_EQ(1, w.get_ID_from_buffer());
}

TEST(WorkerTime, CorrectTimeProcessingPackage) { //wykonywanie pracy: czy robotnik przetwarza półprodukt odpowiednią liczbę tur? czy przekazuje dalej odpowiedni półprodukt?
    PackageQueue q1(PackageQueueType::FIFO);
    PackageQueue q2(PackageQueueType::FIFO);
    std::unique_ptr<IPackageQueue> ptr1 = std::make_unique<PackageQueue>(q1);
    std::unique_ptr<IPackageStockpile> ptr2 = std::make_unique<PackageQueue>(q2);
    Worker w(1, 2,std::move(ptr1));
    Ramp r(1,2);
    Storehouse s(1, std::move(ptr2));
    r.preferences_list_.add_receiver(&w);
    w.preferences_list_.add_receiver(&s);
    r.deliver_goods(0);
    r.send_package();
    w.do_work(0);
    w.send_package();
    r.deliver_goods(1);
    r.send_package();
    w.do_work(1);
    w.send_package();
    r.deliver_goods(2);
    r.send_package();
    w.do_work(2);
    w.send_package();

    EXPECT_EQ(1, s.cbegin()->get_id());
}
