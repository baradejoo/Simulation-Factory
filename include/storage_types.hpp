//    klasy IPackageStockpile, IPackageQueue, PackageQueue
//    typ wyliczeniowy PackageQueueType


#ifndef LAB10_STORAGE_TYPES_HPP
#define LAB10_STORAGE_TYPES_HPP

enum class PackageQueueType{
    FIFO, LIFO
};

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
    void push(Package&&);
    bool empty();
    size_type size();

};



#endif //LAB10_STORAGE_TYPES_HPP
