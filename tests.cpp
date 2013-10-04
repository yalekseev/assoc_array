#include "assoc_array.h"
#include <iostream>
#include <cassert>
#include <string>

void check_result(bool result, const std::string& test_name, std::ostream& os) {
    if (result) {
        os << test_name << " PASSED" << std::endl;
    } else {
        os << test_name << " FAILED" << std::endl;
    }
}

void test_clear() {
    util::assoc_array<int, int> map;

    map[1] = 11;
    map.clear();
    check_result(map.empty(), "Test clear 1", std::cout);

    auto it = map.find(1);
    check_result(it == map.end(), "Test clear 2", std::cout);
}

void test_empty() {
    util::assoc_array<int, int> map;
    check_result(map.empty(), "Test empty 1", std::cout);

    map[1] = 11;
    check_result(!map.empty(), "Test empty 2", std::cout);

    map.erase(1);
    check_result(map.empty(), "Test empty 3", std::cout);
}

void test_size() {
    util::assoc_array<int, int> map;
    check_result(map.size() == 0, "Test size 1", std::cout);

    map[1] = 11; 
    map[2] = 22; 
    map[3] = 33;
    check_result(map.size() == 3, "Test size 2", std::cout);

    map.erase(3);
    check_result(map.size() == 2, "Test size 3", std::cout);

    map.erase(2);
    check_result(map.size() == 1, "Test size 4", std::cout);

    map.erase(1);
    check_result(map.size() == 0, "Test size 5", std::cout);
}

void test_swap() {
    util::assoc_array<int, int> first_map;
    first_map[1] = 11;

    util::assoc_array<int, int> second_map;
    second_map[2] = 22;
    second_map[3] = 33;


    first_map.swap(second_map);

    check_result(first_map.size() == 2, "Test swap 1", std::cout);
    check_result(second_map.size() == 1, "Test swap 2", std::cout);

    {
        auto it = first_map.find(2);
        check_result(it != first_map.end(), "Test swap 3.1", std::cout);

        if (it != first_map.end()) {
            check_result(it->second == 22, "Test swap 3.2", std::cout);
        }
    }

    {
        auto it = first_map.find(3);
        check_result(it != first_map.end(), "Test swap 4.1", std::cout);

        if (it != first_map.end()) {
            check_result(it->second == 33, "Test swap 4.2", std::cout);
        }
    }

    {
        auto it = second_map.find(1);
        check_result(it != second_map.end(), "Test swap 5.1", std::cout);

        if (it != second_map.end()) {
            check_result(it->second == 11, "Test swap 5.2", std::cout);
        }
    }
}

int main() {
    test_clear();
    test_empty();
    test_size();
    test_swap();

    return 0;
}
