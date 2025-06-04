#include <cxxopts.hpp>
#include <fstream>
#include <iostream>

int main(int argc, char *argv[])
{
    cxxopts::Options options("Yawc", "Yet Another Word Counter");

    options.add_options()
    ("c, bytes", "Count bytesize", cxxopts::value<std::string>())
    ("l, lines", "Count lines", cxxopts::value<std::string>());

    auto result = options.parse(argc, argv);

    if (result.count("c"))
    {
        std::string path;

        path = result["c"].as<std::string>();

        std::ifstream file(path);

        if (!file)
        {
            std::cerr << "Error handling file" << '\n';
            return 1;
        }

        file.seekg(0, std::ios::end);

        std::streampos byte_size{file.tellg()};

        if (byte_size != std::streampos(-1))
        {
            std::cout << byte_size << ' ' << path << '\n';
        }
    }

    if (result.count("l"))
    {
        std::string path;

        path = result["l"].as<std::string>();

        std::ifstream file(path);

        if (!file)
        {
            std::cerr << "Error handling file" << '\n';
            return 1;
        }

        int line_counter{};

        for (std::string line; std::getline(file, line);)
        {
            line_counter++;
        }

        std::cout << line_counter << '\n';
    }
    return 0;
}
