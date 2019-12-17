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

class IPackageStockpile{
public:
    using size_type = unsigned int;

    virtual void push(Package&&) = 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
};


class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;
};


class PackageQue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType);
};

#endif //LAB10_STORAGE_TYPES_HPP
