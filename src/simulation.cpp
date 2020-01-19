// 42: Burda (302827), Baradziej (302819), Bytnar (297074)

//
// Created by Kamil Baradziej on 16/01/2020.
//
#include "simulation.hpp"

void simulate(Factory &factory, TimeOffset d, std::function<void(Factory &, Time)> func){
    for(TimeOffset time_ = 1; time_ <= d; time_++){
        factory.do_deliveries(time_);
        factory.do_package_passing();
        factory.do_work(time_);

        func(factory, time_);
    }
}

// 42: Burda (302827), Baradziej (302819), Bytnar (297074)