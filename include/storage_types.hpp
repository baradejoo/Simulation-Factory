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
    virtual Package&& pop() = 0;
    virtual PackageQueueType get_queue_type() = 0;

    //virtual ~IPackageQueue() {}
};


class PackageQueue : public IPackageQueue {
public:
    PackageQueue(PackageQueueType type): queue_type(type){}


    bool empty() override {return packages.empty();}
    void push(Package&&) override {
        packages.push_back(Package&&);
    }
    size_type size() override { return packages.size(); }

    Package&& pop() override {}
    PackageQueueType get_queue_type() override { return queue_type; }

private:
    PackageQueueType queue_type;
    container_type packages;
};

#endif //LAB10_STORAGE_TYPES_HPP
//tymczasowo
PackageQueue p();