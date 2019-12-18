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
    using size_type = unsigned int;
    //using container_type = std::list<Package>::const_iterator ;
    using container_type = std::list<Package> ;

    virtual void push(Package&&) = 0;
    virtual bool empty() = 0;
    virtual size_type size() = 0;

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
    PackageQueue();
    PackageQueue(PackageQueueType);

    container_type kolejka;

    bool empty() override {return 0;}
    void push(Package&&) override {}
    size_type size() override { return 0; }

    Package pop() override {}
    PackageQueueType get_queue_type() override { return typ_kolejki; }

private:
    PackageQueueType typ_kolejki;
};

#endif //LAB10_STORAGE_TYPES_HPP
//tymczasowo
PackageQueue p();