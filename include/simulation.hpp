// 42: Burda (302827), Baradziej (302819), Bytnar (297074)

//
// Created by Kamil Baradziej on 16/01/2020.
//
#include "factory.hpp"
#include "nodes.hpp"
#include "types.hpp"

#ifndef FABRYKA_SIMULATION_HPP
#define FABRYKA_SIMULATION_HPP

void simulate(Factory  &factory, TimeOffset d, std::function<void(Factory&,Time)> func);

#endif //FABRYKA_SIMULATION_HPP

// 42: Burda (302827), Baradziej (302819), Bytnar (297074)