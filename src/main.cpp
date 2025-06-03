#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    cxxopts::Options options("Yawc", "Yet Another Word Counter");

    options.add_options()("c", "Count bytesize", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);

    if (result.count("c"))
    {
        std::string path;

        path = result["c"].as<std::string>();

        std::ifstream file(path);

        if (!file)
        {
            std::cerr << "Error handling file" << '\n';
        }

        file.seekg(0, std::ios::end);

        std::streampos byte_size{file.tellg()};

        if (byte_size != std::streampos(-1))
        {
            std::cout << byte_size << ' ' << path << '\n';
        }
    }
    return 0;
}
