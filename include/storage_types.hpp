// 42: Burda (302827), Baradziej (302819), Bytnar (297074)

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
    using const_iterator = std::list<Package>::const_iterator;

    virtual void push(Package&& package) = 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;
    virtual const_iterator begin() = 0;
    virtual const_iterator cbegin() const = 0;
    virtual const_iterator end() = 0;
    virtual const_iterator cend() const = 0;

    virtual ~IPackageStockpile() {}
};

class IPackageQueue : public IPackageStockpile {
public:
    virtual Package pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;

    //virtual ~IPackageQueue() {}
};


class PackageQueue : public IPackageQueue {
public:
    PackageQueue(const PackageQueueType type): queue_type(type){}
    Package pop() override;
    bool empty() override { return queue.empty(); }
    void push(Package&& package) override {queue.emplace_back(std::move(package));}

    size_type size() override { return queue.size(); }
    const_iterator begin() override { return queue.begin(); }
    const_iterator cbegin() const override { return queue.cbegin(); };
    const_iterator end() override { return queue.end(); };
    const_iterator cend() const override { return queue.cend(); }


    PackageQueueType get_queue_type() override { return queue_type; }

private:
    PackageQueueType queue_type;
    std::list<Package> queue;
};

#endif //LAB10_STORAGE_TYPES_HPP

// 42: Burda (302827), Baradziej (302819), Bytnar (297074)