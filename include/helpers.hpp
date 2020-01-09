// Kamil Baradziej, 302819

#ifndef FABRYKA_HELPERS_HPP
#define FABRYKA_HELPERS_HPP

#include "types.hpp"

#include <iostream>
#include <random>


std::random_device rd;
std::mt19937 rng(rd());

double random_generator() {
   return std::generate_canonical<double, 10>(rng);}

#endif //FABRYKA_HELPERS_HPP
