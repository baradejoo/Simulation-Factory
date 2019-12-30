//
// Created by Robert on 16.12.2019.
//

#include <ntsecpkg.h>
#include "storage_types.hpp"



Package&& PackageQueue::pop() {

    switch (queue_type) {
        case PackageQueueType::FIFO:
            packages.front();
            packages.pop_front();

            break;

        case PackageQueueType::LIFO:
            packages.back();
            packages.pop_back();

            break;
    };
}