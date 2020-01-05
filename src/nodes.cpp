
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
    double random_number = 0.0;

    preferences_list_.insert({r,0});

    for( auto& [key, val] : preferences_list_ )
    {
        key = random_number*(1.0-random_number)
        sum_temp += key
    }
//    for(auto iterator = preferences_list_.begin(); iterator != preferences_list_.end(); iterator++)
//    {
//        iterator ->first = pg()*(1.0-pg())
//        sum_temp += iterator ->first
//    }

    auto it = preferences_list_.end();
    it--;
    it->second = (1.0-sum_temp);

}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double sum_temp = 0.0;
    double random_number = 0.0;

    preferences_list_.erase(r);

    for( auto& [key, val] : preferences_list_ )
    {
        key = random_number*(1.0-random_number)
        sum_temp += key
    }
//    for(auto iterator = preferences_list_.begin(); iterator != preferences_list_.end(); iterator++)
//    {
//        iterator ->first = pg()*(1.0-pg())
//        sum_temp += iterator ->first
//    }

    //auto it = preferences_list_.end()-- ->second = 1.0-sum_temp;
    auto it = preferences_list_.end();
    it--;
    it->second = (1.0-sum_temp);

}

bool compare(std::pair <std::string, int> p, std::pair <std::string, int> q )
{
    return p.second < q.second;
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
//    //for (preferences_t it = begin(); it != end(); it++)


    std::pair<IPackageReceiver*, double> max = (*std::max_element(preferences_list_.begin(), preferences_list_.end(), compare));
    return max.first;

}


