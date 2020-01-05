

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

Ramp::Ramp(ElementID id, TimeOffset di) : id_(id), di_(di) {}

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
    //double sum_temp = 0.0;
    double random_number = pg();

    if (preferences_list_.empty()){
        preferences_list_.insert(std::make_pair(r,1));
    }
    preferences_list_.insert(std::make_pair(r, random_number));
    double sum_temp = 1 + random_number;
    for ( auto& [key, value]: preferences_list_){
        value = value/sum_temp;
    }


}

void ReceiverPreferences::remove_receiver(IPackageReceiver* r) {
    double random_number = pg();

    preferences_list_.erase(r);

    double sum_temp = 1 + random_number;
    for ( auto& [key, value]: preferences_list_){
        value = value/sum_temp;
    }
}

bool compare(std::pair <std::string, int> p, std::pair <std::string, int> q )
{
    return p.second < q.second;
}

IPackageReceiver* ReceiverPreferences::choose_receiver() {
    std::pair<IPackageReceiver*, double> max = (*std::max_element(preferences_list_.begin(), preferences_list_.end(), compare));
    return max.first;
}





