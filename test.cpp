#include "assoc_array.h"
#include <iostream>
#include <cassert>
#include <string>

int main() {
    util::assoc_array<std::string, int> assoc_vector;

    assert(assoc_vector.size() == 0);

    assoc_vector["Yum"] = 10;
    assoc_vector["Baa"] = 23;

    assert(assoc_vector.size() == 2);
    assert(assoc_vector.count("Yum") == 1);
    assert(assoc_vector.count("Baa") == 1);
    assert(assoc_vector.count("AAA") == 0);

    for (auto& p : assoc_vector) {
        std::cout << p.first << " " << p.second << std::endl;
    }

    {
        auto it = assoc_vector.find("AA");
        assert(it == assoc_vector.end());
    }

    {
        auto it = assoc_vector.find("Yum");
        assert(it != assoc_vector.end());
        std::cout << it->second << std::endl;
    }

    return 0;
}
