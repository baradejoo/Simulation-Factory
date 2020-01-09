

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

Worker::Worker(ElementID id, TimeOffset pd, std::unique_ptr<IPackageQueue> q, ReceiverPreferences preferences_list)
        :PackageSender(preferences_list)
{
    id_ = id;
    pd_ = pd;
    q_ = std::move(q);

}
//=========== PackageSender - Function definitions ===========//

void PackageSender::send_package(){
    if(package_sender_buffor_){
        IPackageReceiver* ipackage_receiver_ = preferences_list_.choose_receiver();
        ipackage_receiver_->receive_package(std::move(*package_sender_buffor_));
        package_sender_buffor_.reset();
    }
}

std::optional<Package> PackageSender::get_sending_buffer(){
    if(package_sender_buffor_){
        std::optional<Package> temp_buffor_ = std::move(package_sender_buffor_);
        return temp_buffor_;
    }
    else{
        return std::nullopt;
    }
}

//=============================================================//


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
    double number = probability_generator();
    double sum = 0;
    for (const auto &item: preferences_list_)
    {
        sum += item.second;
        if(number <= sum)
            return item.first;
    }
    return preferences_list_.end()->first;
}





