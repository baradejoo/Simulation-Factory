// 42: Burda (302827), Baradziej (302819), Bytnar (297074)

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

// 42: Burda (302827), Baradziej (302819), Bytnar (297074)