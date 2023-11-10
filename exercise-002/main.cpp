#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>
#include <vector>
#include <random>  // for std::random_device, std::mt19937, std::uniform_int_distribution
#include <algorithm>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    CLI::App app{PROJECT_NAME};
    int count = 20;
    app.add_option("-c,--count", count, "Set the count parameter")->check(CLI::PositiveNumber);

    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
        app.parse(argc, argv);
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }

    fmt::print("Hello, {}! Count: {}\n", app.get_name(), count);

    // Use <random> for better randomness
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(1, 100);

    std::vector<int> randomValues(count);

    for (int &value : randomValues) {
        value = distribution(gen);
    }

    fmt::print("Random values: ");
    for (const int &value : randomValues) {
        fmt::print("{} ", value);
    }
    fmt::print("\n");

    // Sort the vector of random values
    std::sort(randomValues.begin(), randomValues.end());

    // Print the sorted values
    fmt::print("Sorted values: ");
    for (const int &value : randomValues) {
        fmt::print("{} ", value);
    }
    fmt::print("\n");

    return 0; /* exit gracefully */
}