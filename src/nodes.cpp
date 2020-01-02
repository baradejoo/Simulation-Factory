
// Created by Kamil Baradziej on 28/12/2019.


#include "nodes.hpp"

void Worker::receive_package(Package&& prod) {
    //
}

void PackageSender::push_package(Package pack) {
    PackageSenderBuffor.emplace(std::move(pack));
}