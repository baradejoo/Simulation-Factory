//
// Created by Bartolemello on 16.01.2020.
//


#ifndef FABRYKA_FACTORY_HPP
#define FABRYKA_FACTORY_HPP

#include <iostream>
#include <vector>
#include "types.hpp"

class Factory{
public:

private:
};

template <class Node>
class NodeCollection {

    using container_t = typename std::vector<Node>;
    using iterator = typename container_t::iterator;
    using const_iterator = typename container_t::const_iterator;

    const_iterator cbegin() const { return nodes_.cbegin(); }
    const_iterator cend() const { return nodes_.cend(); }
    iterator begin() { return nodes_.begin(); }
    const_iterator begin() const { return nodes_.cbegin(); }
    iterator end() { return nodes_.end(); }
    const_iterator end() const { return nodes_.cend(); }

public:
   // NodeCollection(const std::vector<ReceiverType>& nodes_container) : nodes_container(nodes_container) {}
    void add(Node& node) {nodes_.push_back(std::move(node));}

    void remove_by_id(ElementID id_){
        if(find_by_id(id_) != end())
        nodes_.erase(find_by_id(id_));
    }

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

#endif //FABRYKA_FACTORY_HPP

