

// Created by Kamil Baradziej on 28/12/2019.


#include <nodes.hpp>

#include "nodes.hpp"

void Worker::do_work(Time t) {
    if((t-t_)%pd_ == 0){
        if(WorkerBuffer) {
            push_package(std::move(*WorkerBuffer));
            WorkerBuffer.reset();
        }
        WorkerBuffer.emplace(q_->pop());
        //send_package();
        t_=t;
    }

}

void PackageSender::push_package(Package&& pack) {
    PackageSenderBuffor.emplace(std::move(pack));
}


void Ramp::deliver_goods(Time t)
{
    if(t % di_ == 0)
    {
        Package package;
        push_package(std::move(package));
        //send_package();
    }
}

void Worker::receive_package(Package&& prod) {
    q_->push(std::move(prod));
}

void Storehouse::receive_package(Package&& pck)
{
    d_->push(std::move(pck));

}

//Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q)
//{
//    id_ = id;
//    pd_ = pd;
//    q_ = std::move(q);
//    preferences_list_ = preferences_list;
//}

void PackageSender::send_package()
{
    if(PackageSenderBuffor)
    {
        preferences_list_.choose_receiver()->receive_package(std::move(*PackageSenderBuffor));
        PackageSenderBuffor.reset();
    }
}


void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    double sum_temp = 0.0;

    preferences_list_.emplace(std::make_pair(r, 1.0));

    for(const auto& item: preferences_list_)
    {
        sum_temp+= item.second;
    }

    for(auto& item: preferences_list_)
    {
        item.second /= sum_temp;
    }

}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double sum_temp = 0.0;

    preferences_list_.erase(r);

    for(const auto& item: preferences_list_)
    {
        sum_temp+= item.second;
    }

    for(auto& item: preferences_list_)
    {
        item.second /= sum_temp;
    }

}


IPackageReceiver* ReceiverPreferences::choose_receiver()
{
    double number = pg();
    double sum = 0;
    for (const auto &item: preferences_list_)
    {
        sum += item.second;
        if(number <= sum)
            return item.first;
    }
    return preferences_list_.end()->first;
}





