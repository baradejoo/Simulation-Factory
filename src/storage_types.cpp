//
// Created by Robert on 16.12.2019.
//

#include "storage_types.hpp"

Package PackageQueue::pop() {
    Package put_package;
    switch(queue_type){
        case PackageQueueType::FIFO: {
            put_package = std::move(queue.front());
            queue.pop_front();
            break;
        }
        case PackageQueueType::LIFO: {
            put_package = std::move(queue.back());
            queue.pop_back();
            break;
        }
    }
    return put_package;
}
