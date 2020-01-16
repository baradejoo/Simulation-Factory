//
// Created by Bartolemello on 16.01.2020.
//
#include "factory.hpp"

void Factory::do_deliveries(Time time){
    std::for_each(Ramps.begin(), Ramps.end(), [time](Ramp & ramp_) { ramp_.deliver_goods(time); });
}

void Factory::do_package_passing() {
    std::for_each(Ramps.begin(), Ramps.end(), [](Ramp & ramp_){ ramp_.send_package(); });
    std::for_each(Workers.begin(),Workers.end(),[](Worker & worker_) { worker_.send_package(); });
}

void Factory::do_work(Time time) {
    std::for_each(Workers.begin(), Workers.end(), [time](Worker & worker_) { worker_.do_work(time); });
}

template <typename Node>
void Factory::remove_receiver(NodeCollection<Node>& collection_, ElementID id){
    collection_.remove_by_id(id);

    auto ramp_vec = std::find_if(Ramps.begin(), Ramps.end(), [id](auto& element){
        return id == element.receiver_preferences_.get_preferences()->first; });

    for (auto& ramp: ramp_vec) {
        ramp.receiver_preferences_.remove_receiver(&collection_.find_ramp_by_id(id));
    }

    auto worker_vec = std::find_if(Workers.begin(), Workers.end(), [id](auto& element) {
        return id == element.receiver_preferences_.get_preferences()->first; });

    for (auto& worker: worker_vec) {
        worker.receiver_preferences_.remove_receiver(&collection_.find_worker_by_id(id));
    }
}