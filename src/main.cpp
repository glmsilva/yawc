#include <cxxopts.hpp>
#include <iostream>

int main(int argc, char *argv[])
{
    cxxopts::Options options("Yawc", "Yet Another Word Counter");

    options.add_options()
    ("c", "Count bytesize");

    auto result = options.parse(argc, argv);
    
    if(result.count("c")) {
        std::cout << "Bytesize" << '\n';
    }
    return 0;
}