#include <fmt/chrono.h>
#include <fmt/format.h>
#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <algorithm>

#include "CLI/CLI.hpp"
#include "config.h"

auto main(int argc, char **argv) -> int
{
    /**
     * CLI11 is a command line parser to add command line options
     * More info at https://github.com/CLIUtils/CLI11#usage
     */
    CLI::App app{PROJECT_NAME};
    int count = 20;
    app.add_option("-c,--count", count, "Set the count parameter")->check(CLI::PositiveNumber);
    try
    {
        app.set_version_flag("-V,--version", fmt::format("{} {}", PROJECT_VER, PROJECT_BUILD_DATE));
       
    }
    catch (const CLI::ParseError &e)
    {
        return app.exit(e);
    }
    
    /**
     * The {fmt} lib is a cross platform library for printing and formatting text
     * it is much more convenient than std::cout and printf
     * More info at https://fmt.dev/latest/api.html
     */
    fmt::print("Hello, {}! Count: {}\n", app.get_name(), count);

    /* INSERT YOUR CODE HERE */
     std::srand(std::time(nullptr)); // Seed für die Zufallsgenerierung
    std::vector<int> randomValues(count);

    for (int &value : randomValues) {
        value = std::rand() % 100 + 1; // Zufallszahl von 1 bis 100 generieren
    }

    // Ausgabe der zufälligen Werte
    fmt::print("Random values: ");
    for (const int &value : randomValues) {
        fmt::print("{} ", value);
    }
    fmt::print("\n");

    std::sort(randomValues.begin(), randomValues.end());

    // Gib die sortierten Werte aus
    fmt::print("Sorted values: ");
    for (const int &value : randomValues) {
        fmt::print("{} ", value);
    }
    fmt::print("\n");


    return 0; /* exit gracefully*/
}
