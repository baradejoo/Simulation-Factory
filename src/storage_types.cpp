//
// Created by Robert on 16.12.2019.
//

#include "storage_types.hpp"

Package PackageQueue::pop() {
    switch(queue_type){
        case PackageQueueType::FIFO: {
            Package put_package = std::move(queue.front());
            queue.pop_front();
            return put_package;
            break;
        }
        case PackageQueueType::LIFO: {
            Package put_package = std::move(queue.back());
            queue.pop_back();
            return put_package;
            break;
        }
    }
}
