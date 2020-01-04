//
// Created by Kamil Baradziej on 28/12/2019.
//

#ifndef FABRYKA_HELPERS_HPP
#define FABRYKA_HELPERS_HPP

#include "types.hpp"

#include <iostream>
#include <random>


std::random_device rd;
std::mt19937 rng(rd());

double pg() {
   return std::generate_canonical<double, 10>(rng);}

#endif //FABRYKA_HELPERS_HPP
