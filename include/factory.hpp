//
// Created by Bartolemello on 16.01.2020.
//


#ifndef FABRYKA_FACTORY_HPP
#define FABRYKA_FACTORY_HPP

#include <iostream>
#include <vector>
#include "types.hpp"
#include "nodes.hpp"

#include <nodes.hpp>
#include <iostream>

enum class NodeColor{
    UNVISITED, VISITED, VERIFIED
};

template <typename Node>
class NodeCollection{
public:
    //aliasy
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;
    //gettery
    NodeCollection<Node>::iterator find_by_id(ElementID id_) { return std::find_if(container_.begin(), container_.end(), [id_](const Node& x){ return id_ == x.get_id();});}
    NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const { return std::find_if(container_.cbegin(), container_.cend(), [id_](const Node& x){ return id_ == x.get_id();}); }
    NodeCollection<Node>::iterator begin(){ return container_.begin(); }
    NodeCollection<Node>::iterator end(){ return container_.end(); }
    NodeCollection<Node>::const_iterator begin() const{ return container_.cbegin(); }
    NodeCollection<Node>::const_iterator cbegin() const{ return container_.cbegin(); }
    NodeCollection<Node>::const_iterator end() const{ return container_.cend(); }
    NodeCollection<Node>::const_iterator cend() const{ return container_.cend(); }
    //settery
    void add(Node& node) { container_.emplace_back(std::move(node));}
    void remove_by_id(ElementID id_)
    {
        auto it = find_by_id(id_);
        if(it != container_.end())
            container_.erase(it,++it);
    }
private:
    container_t container_;
};

class Factory{
public:
    void add_ramp(Ramp&& r){collection_of_ramps_.add(r);}
    void remove_ramp(ElementID id){collection_of_ramps_.remove_by_id(id);}
    NodeCollection<Ramp>::iterator find_ramp_by_id(ElementID id){return collection_of_ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator find_ramp_by_id(ElementID id) const{return collection_of_ramps_.find_by_id(id);}
    NodeCollection<Ramp>::const_iterator ramp_cbegin()const{return collection_of_ramps_.cbegin();}
    NodeCollection<Ramp>::const_iterator ramp_cend()const{return collection_of_ramps_.cend();}

    void add_worker(Worker&& w){collection_of_workers_.add(w);}
    void remove_worker(ElementID id){this -> remove_receiver(collection_of_workers_,id);}
    NodeCollection<Worker>::iterator find_worker_by_id(ElementID id){return collection_of_workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator find_worker_by_id(ElementID id) const{return collection_of_workers_.find_by_id(id);}
    NodeCollection<Worker>::const_iterator worker_cbegin()const{return collection_of_workers_.cbegin();}
    NodeCollection<Worker>::const_iterator worker_cend()const{return collection_of_workers_.cend();}

    void add_storehouse(Storehouse&& s){collection_of_stores_.add(s);}
    void remove_storehouse(ElementID id){this -> remove_receiver(collection_of_stores_,id);}
    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){return collection_of_stores_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const{return collection_of_stores_.find_by_id(id);}
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin()const{return collection_of_stores_.cbegin();}
    NodeCollection<Storehouse>::const_iterator storehouse_cend()const{return collection_of_stores_.cend();}

    bool is_consistent() const ;
    void do_deliveries(Time);
    void do_package_passing();
    void do_work(Time);
private:
    template <typename Node>
    void remove_receiver(NodeCollection<Node>& collection, ElementID id){
        ReceiverType rt = collection.begin()->get_receiver_type();
        collection.remove_by_id(id);
        if(rt == ReceiverType::Worker) {
            for (auto &ramp: collection_of_ramps_) {
                for (auto &preference: ramp.receiver_preferences_) {
                    if (preference.first->get_id() == id) {
                        ramp.receiver_preferences_.remove_receiver(preference.first);
                        break;
                    }
                }
            }
        }
        else {
            for (auto &worker: collection_of_workers_) {
                for (auto &preference: worker.receiver_preferences_) {
                    if (preference.first->get_id() == id) {
                        worker.receiver_preferences_.remove_receiver(preference.first);
                        break;
                    }
                }
            }
        }
    }

    NodeCollection<Ramp> collection_of_ramps_;
    NodeCollection<Worker> collection_of_workers_;
    NodeCollection<Storehouse> collection_of_stores_;
};

#endif //FABRYKA_FACTORY_HPP

