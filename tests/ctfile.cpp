#include "file/ctfile.hpp"

#include "random.hpp"

#include <cassert>
#include <string>
#include <iostream>

const std::string filepath = "file_ctfile_test.bin";


void test_vector();
void test_unordered_map();
void test_vector_vector();
void test_vector_unordered_map();
void test_unordered_map_vector();
void test_string();
void test_string_vector();
void test_string_unordered_map();

int main()
{
    test_vector();
    test_unordered_map();
    test_vector_vector();
    test_vector_unordered_map();
    test_unordered_map_vector();
    test_string();
    test_string_vector();
    test_string_unordered_map();
};



void test_vector()
{
    typedef std::vector<int> data_t;
    data_t data = make_vector();
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        for (int i = 0; i < depth; i++) { assert(file.data()[i] == data[i]); };
    }
    std::cout << "vector<int> test passed\n";
};
void test_unordered_map()
{
    typedef std::unordered_map<int, int> data_t;
    data_t data = make_unordered_map();
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        for (int i = 0; i < depth; i++) { assert(file.data()[i] == data[i]); };
    }
    std::cout << "unordered_map<int, int> test passed\n";
};
void test_vector_vector()
{
    typedef std::vector<int> nested_data_t;
    typedef std::vector<nested_data_t> data_t;
    data_t data;
    data.resize(depth);
    for (int i = 0; i < depth; i++) { data[i] = make_vector(); }
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        for (int i = 0; i < depth; i++) {
            nested_data_t &nested_filedata = file.data()[i];
            nested_data_t &nested_data = data[i];
            for (int j = 0; j < depth; j++) { assert(nested_data[j] == nested_filedata[j]); }
        };
    }
    std::cout << "vector<vector<int>> test passed\n";

};
void test_vector_unordered_map()
{
    typedef std::vector<int> nested_data_t;
    typedef std::unordered_map<int, nested_data_t> data_t;
    data_t data;
    for (int i = 0; i < depth; i++) { data[i] = make_vector(); }
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        for (int i = 0; i < depth; i++) {
            nested_data_t &nested_filedata = file.data()[i];
            nested_data_t &nested_data = data[i];
            for (int j = 0; j < depth; j++) { assert(nested_data[j] == nested_filedata[j]); }
        };
    }
    std::cout << "unordered_map<int, vector<int>> test passed\n";

};
void test_unordered_map_vector()
{
    typedef std::unordered_map<int, int> nested_data_t;
    typedef std::vector<nested_data_t> data_t;
    data_t data;
    data.resize(depth);
    for (int i = 0; i < depth; i++) { data[i] = make_unordered_map(); }
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        for (int i = 0; i < depth; i++) {
            nested_data_t &nested_filedata = file.data()[i];
            nested_data_t &nested_data = data[i];
            for (int j = 0; j < depth; j++) { assert(nested_data[j] == nested_filedata[j]); }
        };
    }
    std::cout << "vector<unordered_map<int, int>> test passed\n";

};
void test_string()
{
    typedef std::string data_t;
    data_t data = make_string();
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        assert(file.data() == data); 
    }
    std::cout << "string test passed\n";
};
void test_string_vector()
{
    typedef std::vector<std::string> data_t;
    data_t data;
    data.resize(depth);
    for (int i = 0; i < depth; i++) { data[i] = make_string(); }
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        for (int i = 0; i < depth; i++) { assert(file.data()[i] == data[i]); };
    }
    std::cout << "vector<string> test passed\n";
};
void test_string_unordered_map()
{
    typedef std::unordered_map<int, std::string> data_t;
    data_t data;
    for (int i = 0; i < depth; i++) { data[i] = make_string(); }
    {
        libfile::ctfile<data_t> file(filepath);
        file.data() = data;
        file.save();
    }
    {
        libfile::ctfile<data_t> file(filepath);
        file.load();
        for (int i = 0; i < depth; i++) { assert(file.data()[i] == data[i]); };
    }
    std::cout << "unordered_map<int, string> test passed\n";
};
