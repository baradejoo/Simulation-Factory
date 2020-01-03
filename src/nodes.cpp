
// Created by Kamil Baradziej on 28/12/2019.


#include <nodes.hpp>

#include "nodes.hpp"

void Worker::do_work(Time t) {
    if((t-t_)%pd_ == 0){
        if(WorkerBuffer) {
            push_package(std::move(*WorkerBuffer));
            WorkerBuffer.reset();
        }
        WorkerBuffer.emplace(q_->pop());
        send_package();
    }
    t_=t;
}

void PackageSender::push_package(Package pack) {
    PackageSenderBuffor.emplace(std::move(pack));
}

void Ramp::deliver_goods(Time t) {
    if(t%di_ == 0){
        Package package;
        push_package(std::move(package));
    }
}

void Worker::receive_package(Package&& prod) {
    q_->push(std::move(prod));
}


//void PackageSender::send_package() {
//    if(PackageSenderBuffor){
//
//    }
//}

//void ReceiverPreferences::add_reciever(IPackageReceiver* r) {
//    //preferences_t.ins
//}
//
//void ReceiverPreferences::remove_reciever(IPackageReceiver* r) {
//   //preferences_t.erase()
//}
//
//IPackageReceiver* ReceiverPreferences::choose_receiver() {
//    //for (preferences_t it = begin(); it != end(); it++)
//}
