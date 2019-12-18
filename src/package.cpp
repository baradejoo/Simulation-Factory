//
// Created by Bartolemello on 13.12.2019.
//
#include <package.hpp>
#include "package.hpp"
#include <algorithm>



Package::Package() {
    if(!freed_IDs_.empty()){
        id_ = *std::min_element(freed_IDs_.cbegin(), freed_IDs_.end());
        assigned_IDs_.insert(id_);
        freed_IDs_.erase(id_);
    }else{
       id_ =  *std::max_element(assigned_IDs_.cbegin(), assigned_IDs_.end()) + 1;
       assigned_IDs_.insert(id_);
    }
}

Package::Package(Package&& p){
    id_ = p.id_;
}

Package::~Package() {
    assigned_IDs_.erase(id_);
    freed_IDs_.insert(id_);
}


//Package& Package::operator=(Package&& p) {
//    id_ = p.id_;
//    return *this;
//}

