#pragma once

#include <random>
#include <vector>
#include <unordered_map>
#include <string>

constexpr int depth = 1000;

std::random_device rd;
std::mt19937 gen(rd());

std::uniform_int_distribution int_dis(1,1000000);
std::uniform_int_distribution char_dis(32,127);

std::vector<int> make_vector()
{
    std::vector<int> data;
    data.resize(1000);
    for (int i = 0; i < depth; i++) { data[i] = int_dis(gen); };
    return data;
};
std::unordered_map<int, int> make_unordered_map()
{
    std::unordered_map<int, int> data;
    for (int i = 0; i < depth; i++) { data[i] = int_dis(gen); };
    return data;
};
std::string make_string()
{
    std::string data;
    data.resize(1000);
    for (int i = 0; i < depth; i++) { data[i] = char_dis(gen); };
    return data;
};
