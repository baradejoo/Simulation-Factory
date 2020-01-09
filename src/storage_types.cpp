// Kamil Baradziej, 302819

#include "storage_types.hpp"

Package PackageQueue::pop() {
    Package package;
    switch(queue_type){
        case PackageQueueType::FIFO: {
            package = std::move(queue.front());
            queue.pop_front();
            break;
        }
        case PackageQueueType::LIFO: {
            package = std::move(queue.back());
            queue.pop_back();
            break;
        }
    }
    return package;
}
