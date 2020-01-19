// 42: Burda (302827), Baradziej (302819), Bytnar (297074)

//
// Created by Bartolemello on 16.01.2020.
//

#ifndef FABRYKA_FACTORY_HPP
#define FABRYKA_FACTORY_HPP

#include <iostream>
#include "types.hpp"
#include "nodes.hpp"


enum class NodeColor{
    VISITED, UNVISITED,  VERIFIED
};


//=====================================//
//=========== NodeCollection ==========//

template <typename Node>

class NodeCollection{
public:

    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    NodeCollection<Node>::const_iterator begin() const{ return nodes_.cbegin(); }
    NodeCollection<Node>::const_iterator cbegin() const{ return nodes_.cbegin(); }
    NodeCollection<Node>::iterator begin(){ return nodes_.begin(); }
    NodeCollection<Node>::iterator end(){ return nodes_.end(); }
    NodeCollection<Node>::const_iterator end() const{ return nodes_.cend(); }
    NodeCollection<Node>::const_iterator cend() const{ return nodes_.cend(); }

    void add(Node& node) { nodes_.emplace_back(std::move(node));}

    NodeCollection<Node>::iterator find_by_id(ElementID id_) {
        return std::find_if(nodes_.begin(), nodes_.end(), [id_](const Node& node){ return id_ == node.get_id();});
    }
    NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const {
        return std::find_if(nodes_.cbegin(), nodes_.cend(), [id_](const Node& node){ return id_ == node.get_id();});
    }
    void remove_by_id(ElementID id_)
    {
        auto it = find_by_id(id_);
        if(it != nodes_.end())
            nodes_.erase(it,++it);
    }

private:
    container_t nodes_;
};

//=====================================//
//============= Factory ===============//

class Factory{
public:

    void add_ramp(Ramp&& x){ramps_.add(x);}
    void remove_ramp(ElementID id){ramps_.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){return ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const{return ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin()const{return ramps_.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend()const{return ramps_.cend();}

    void add_worker(Worker&& y){workers_.add(y);}
    void remove_worker(ElementID id){ remove_receiver(workers_,id);}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const{return workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin()const{return workers_.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend()const{return workers_.cend();}

    void add_storehouse(Storehouse&& z){stores_.add(z);}
    void remove_storehouse(ElementID id){ remove_receiver(stores_,id);}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){return stores_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const{return stores_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin()const{return stores_.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend()const{return stores_.cend();}

    bool is_consistent() const ;
    void do_deliveries(Time);
    void do_package_passing();
    void do_work(Time);

private:
    template <typename Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id){
        ReceiverType r_type = collection.begin()->get_receiver_type();
        collection.remove_by_id(id);
        if(r_type == ReceiverType::Worker) {
            for (auto& ramp: ramps_) {
                for (auto& preference: ramp.receiver_preferences_) {
                    if (preference.first->get_id() == id) {
                        ramp.receiver_preferences_.remove_receiver(preference.first);
                        break;
                    }
                }
            }
        }
        else {
            for (auto &worker: workers_) {
                for (auto &preference: worker.receiver_preferences_) {
                    if (preference.first->get_id() == id) {
                        worker.receiver_preferences_.remove_receiver(preference.first);
                        break;
                    }
                }
            }
        }
    }

    NodeCollection<Ramp> ramps_;
    NodeCollection<Worker> workers_;
    NodeCollection<Storehouse> stores_;
};

#endif //FABRYKA_FACTORY_HPP

// 42: Burda (302827), Baradziej (302819), Bytnar (297074)