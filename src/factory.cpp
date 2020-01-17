//
// Created by Bartolemello on 16.01.2020.
//
#include "factory.hpp"

bool has_reachable_storehouse(const PackageSender* sender, std::map<const PackageSender*, NodeColor>& node_colors){
    if(node_colors[sender] == NodeColor::VERIFIED)
        return true;
    node_colors[sender] = NodeColor::VISITED;

    if(sender->receiver_preferences_.get_preferences().empty())
        return false;

    bool has_receiver_flag = false;
    bool has_storehouse_reachable = false;
    int bad_nodes = 0;
    for(auto receiver : sender->receiver_preferences_.get_preferences()) {
        if (receiver.first->get_receiver_type() == ReceiverType::Storehouse){
            has_receiver_flag = true;
            has_storehouse_reachable = true;
        }
        else{
            auto worker_ptr = dynamic_cast<Worker*>(receiver.first);
            if(worker_ptr == sender)
                continue;
            has_receiver_flag = true;
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            if(node_colors[sendrecv_ptr] == NodeColor::UNVISITED)
                has_storehouse_reachable = has_reachable_storehouse(sendrecv_ptr, node_colors);
        }
        if(!has_storehouse_reachable || !has_receiver_flag)bad_nodes++;
    }
    node_colors[sender] = NodeColor::VERIFIED;
    if(has_storehouse_reachable && has_receiver_flag && bad_nodes == 0)
        return true;
    else return false;
}

//=====================================//
//============= Factory ===============//

bool Factory::is_consistent() const {
    std::map<const PackageSender*, NodeColor> node_colors;
    node_colors.clear();
    for(auto& ramp: ramps_) {
        Ramp *rptr = const_cast<Ramp *>(&ramp);
        node_colors.insert({dynamic_cast<PackageSender *>(rptr), NodeColor::UNVISITED});
    }
    for(auto& worker: workers_) {
        Worker *wptr = const_cast<Worker *>(&worker);
        node_colors.insert({dynamic_cast<PackageSender *>(wptr), NodeColor::UNVISITED});
    }

    for(auto& ramp: ramps_) {
        try {

            if(!has_reachable_storehouse(&ramp,node_colors))
                return false;
        } catch (std::logic_error())
        {
            return false;
        }
    }
    return true;
}

void Factory::do_deliveries(Time time) {
    for(auto& ramps: ramps_){
        ramps.deliver_goods(time);
    }
}

void Factory::do_package_passing() {
    for(auto& ramp: ramps_){
        if(ramp.get_sending_buffer().has_value()){
            ramp.send_package();
        }
    }
    for(auto& worker: workers_){
        if(worker.get_sending_buffer().has_value()){
            worker.send_package();
        }
    }
}

void Factory::do_work(Time time) {
    for(auto& worker: workers_){
        worker.do_work(time);
    }
}
