
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
        send_package();
    }
    t_=t;
}

void PackageSender::push_package(Package pack) {
    PackageSenderBuffor.emplace(std::move(pack));
}

void Ramp::deliver_goods(Time t) {
    if(t%di_ == 0){

    }
}

void Worker::receive_package(Package&& prod) {
    q_->push(std::move(prod));
}


//void PackageSender::send_package() {
//    if(PackageSenderBuffor){
//
//    }
//}

void ReceiverPreferences::add_receiver(IPackageReceiver* r) {
    double sum_temp = 0.0;

    preferences_list_.insert(std::pair<IPackageReceiver*, double> (r,0))

    for( auto& [key, val] : preferences_list_ )
    {
        key = pg()*(1.0-pg())
        sum_temp += key
    }

    auto it = preferences_list_.end();
    it--;
    it->second = (1.0-sum_temp);

}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double sum_temp = 0.0;
    //auto it = preferences_list_.end();

    preferences_list_.erase(std::pair<IPackageReceiver*, double> (r,0))

    for( auto& [key, val] : preferences_list_ )
    {
        key = pg()*(1.0-pg())
        sum_temp += key
    }

    //auto it = preferences_list_.end()-- ->second = 1.0-sum_temp;
    auto it = preferences_list_.end();
    it--;
    it->second = (1.0-sum_temp);

}

//IPackageReceiver* ReceiverPreferences::choose_receiver() {
//    //for (preferences_t it = begin(); it != end(); it++)
//}


