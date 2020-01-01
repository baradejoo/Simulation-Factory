// <<interface>> IPackageStockpile, <<interface>> IPackageQueue //
// <<class>> PackageQueue //
// <<enumeration>> PackageQueueType //

#ifndef LAB10_STORAGE_TYPES_HPP
#define LAB10_STORAGE_TYPES_HPP

#include <deque>
#include <iostream>
#include <list>
#include "package.hpp"

enum class PackageQueueType{
    FIFO, LIFO
};

class const_iterator;

class IPackageStockpile{
public:
    using containerIt = std::list<Package>::const_iterator;

    virtual void push(Package&& package) = 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
    virtual containerIt begin() = 0;
    virtual const containerIt cbegin() = 0;
    virtual containerIt end() = 0;
    virtual const containerIt cend() = 0;

    virtual ~IPackageStockpile() {}
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;

    virtual ~IPackageQueue() {}
};


class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType type): queue_type(type){}

    bool empty() override { return queue.empty(); }
    void push(Package&& package) override { queue.emplace_back(std::move(package)); }
    size_type size() override { return queue.size(); }
    containerIt begin() override { return queue.begin(); }
    const containerIt cbegin() override { return queue.cbegin(); };
    containerIt end() override { return queue.end(); };
    const containerIt cend() override { return queue.cend(); }

    Package pop() override;
    PackageQueueType get_queue_type() override { return queue_type; }


private:
    PackageQueueType queue_type;
    std::list<Package> queue;
};

#endif //LAB10_STORAGE_TYPES_HPP
