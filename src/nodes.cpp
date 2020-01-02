
// Created by Kamil Baradziej on 28/12/2019.


#include <nodes.hpp>

#include "nodes.hpp"

void Worker::receive_package(Package&& prod) {
    //
}



void PackageSender::push_package(Package pack) {
    PackageSenderBuffor.emplace(std::move(pack));
}

void ReceiverPreferences::add_reciever(IPackageReceiver* r) {
    //preferences_t.ins
}

void ReceiverPreferences::remove_reciever(IPackageReceiver* r) {
   //preferences_t.erase()
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    //for (preferences_t it = begin(); it != end(); it++)
}
