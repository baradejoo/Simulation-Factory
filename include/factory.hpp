//
// Created by Bartolemello on 16.01.2020.
//


#ifndef FABRYKA_FACTORY_HPP
#define FABRYKA_FACTORY_HPP

#include <iostream>
#include <vector>
#include "types.hpp"
#include "nodes.hpp"

template <typename Node>
class NodeCollection {
public:
    using container_t = typename std::list<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    const_iterator cbegin() const { return nodes_.cbegin(); }
    const_iterator cend() const { return nodes_.cend(); }
    iterator begin() { return nodes_.begin(); }
    const_iterator begin() const { return nodes_.cbegin(); }
    iterator end() { return nodes_.end(); }
    const_iterator end() const { return nodes_.cend(); }

    void add(Node& node) { nodes_.emplace_back(std::move(node)); }
    void remove_by_id(ElementID id_);

    NodeCollection<Node>::iterator find_by_id(ElementID id_){
        auto is_id_equal = [id_] (const Node& node){return node.get_id()==id_;};
        return std::find_if(begin(), end(), is_id_equal());
    }

    NodeCollection<Node>::const_iterator find_by_id(ElementID id_) const {
        auto is_id_equal = [id_] (const Node& node){return node.get_id()==id_;};
        return std::find_if(cbegin(),cend(), is_id_equal());
    }


private:
    std::vector<Node> nodes_;

};


class Factory{
public:
    void do_package_passing();
    bool is_consistent();
    void do_work(Time time);
    void do_deliveries(Time time);


//==================== Storehouse - function ====================//
    void add_storehouse(Storehouse && nodes){ Storehouses.add(nodes); }
    void remove_storehouse(ElementID id) {};

    NodeCollection<Storehouse>::iterator find_storehouse_by_id(ElementID id){ return Storehouses.find_by_id(id); }
    NodeCollection<Storehouse>::const_iterator find_storehouse_by_id(ElementID id) const { return Storehouses.find_by_id(id); }
    NodeCollection<Storehouse>::const_iterator storehouse_cbegin(){ return Storehouses.cbegin(); }
    NodeCollection<Storehouse>::const_iterator storehouse_cend(){ return Storehouses.cend(); }
//===============================================================//

private:
    NodeCollection<Storehouse> Storehouses;
    NodeCollection<Worker> Workers;
    NodeCollection<Ramp> Ramps;
    void remove_receiver(NodeCollection<Node>& collection_, ElementID id);

};

template<typename Node>
void NodeCollection<Node>::remove_by_id(ElementID id_){
    NodeCollection::iterator iter = find_by_id(id_);
    if(iter != nodes_.end()){
        nodes_.erase(iter);
    }
}

#endif //FABRYKA_FACTORY_HPP

