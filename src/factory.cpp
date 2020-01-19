// 42: Burda (302827), Baradziej (302819), Bytnar (297074)
//
// Created on 16.01.2020.
//
#include "factory.hpp"

bool is_storehouse_available(std::map<const PackageSender*, NodeColor>& node_colors, const PackageSender* sender) {

    if(node_colors[sender] == NodeColor::VERIFIED) {
        return true;
    }

    node_colors[sender] = NodeColor::VISITED;
    if(sender->receiver_preferences_.get_preferences().empty()) {
        return false;
    }

    bool storehouse_avail = false;
    int invalid_nodes = 0;
    bool flag_avail = false;

    for(auto receiver : sender->receiver_preferences_.get_preferences()) {
        if (receiver.first->get_receiver_type() == ReceiverType::Storehouse){
            storehouse_avail = true;
            flag_avail = true;
        }
        else{
            auto worker_ptr = dynamic_cast<Worker*>(receiver.first);
            if(worker_ptr == sender)
                continue;
            auto sendrecv_ptr = dynamic_cast<PackageSender*>(worker_ptr);
            flag_avail = true;
            if(node_colors[sendrecv_ptr] == NodeColor::UNVISITED)
                storehouse_avail = is_storehouse_available(node_colors, sendrecv_ptr);
        }
        if(!storehouse_avail || !flag_avail){
            invalid_nodes++;
        }
    }
    node_colors[sender] = NodeColor::VERIFIED;
    return  invalid_nodes == 0 &&storehouse_avail && flag_avail;
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

            if(!is_storehouse_available(node_colors, &ramp))
                return false;
        } catch (std::logic_error())
        {
            return false;
        }
    }
    return true;
}




void Factory::do_work(Time time) {
    for(auto& worker: workers_){
        worker.do_work(time);
    }
}

void Factory::do_package_passing() {
    for(auto& ramp: ramps_){
        if((ramp.get_sending_buffer()).has_value()){
            ramp.send_package();
        }
    }
    for(auto& worker: workers_){
        if((worker.get_sending_buffer()).has_value()){
            worker.send_package();
        }
    }
}

void Factory::do_deliveries(Time time) {
    for(auto& ramps: ramps_){
        ramps.deliver_goods(time);
    }
}



// 42: Burda (302827), Baradziej (302819), Bytnar (297074)