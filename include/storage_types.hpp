// <<interface>> IPackageStockpile, <<interface>> IPackageQueue //
// <<class>> PackageQueue //
// <<enumeration>> PackageQueueType //

#ifndef LAB10_STORAGE_TYPES_HPP
#define LAB10_STORAGE_TYPES_HPP

#include <deque>
#include <iostream>
#include "package.hpp"

enum class PackageQueueType{
    FIFO, LIFO
};

class const_iterator;

/*
class PackageQue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType);
};

class IPackageQueue : public IPackageStockpile {
public:
    Package pop()
    PackageQueueType const get_queue_type()
};

class IPackageStockpile{
public:
    using container_type=std::deque<Package>;
    using size_type=unsigned int;

    void push(Package&&) {container_type.push_back(&Package);}
    bool empty() const {return container_type.empty()
    size_type size() const {return container_type.size();}

};

*/

#endif //LAB10_STORAGE_TYPES_HPP
