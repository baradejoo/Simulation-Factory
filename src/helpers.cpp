//=============== default_probability_generator - definition ================//

#include "helpers.hpp"

std::random_device rd;
std::mt19937 rng_(rd());

double default_probability_generator(){
    double rand_temp = std::generate_canonical<double, 10>(rng_);
    return rand_temp;
}

std::function<double()> probability_generator = default_probability_generator;