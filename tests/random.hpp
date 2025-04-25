#pragma once

#include <random>
#include <vector>
#include <unordered_map>
#include <string>

constexpr int container_depth = 100;

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution int_dis(1,2000000000);
std::uniform_int_distribution char_dis(32,127);

std::vector<int> make_vector()
{
    std::vector<int> data;
    data.resize(container_depth);
    for (int i = 0; i < container_depth; i++) { data[i] = int_dis(gen); };
    return data;
};
std::unordered_map<int, int> make_unordered_map()
{
    std::unordered_map<int, int> data;
    for (int i = 0; i < container_depth; i++) { data.insert({i, int_dis(gen)}); };
    return data;
};
std::string make_string()
{
    std::string data;
    data.resize(container_depth);
    for (int i = 0; i < container_depth; i++) { data[i] = char_dis(gen); };
    return data;
};
