#include "run.hpp"

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>
#include <cstring>

#include "helpers.hpp"

using namespace std;
namespace fs = filesystem;

void run() {
    if (!fs::exists("buildc") || fs::is_empty("buildc"))
        help::logger::exitWithError("[err] Not a BuildC project");

    string file;
    help::for_build::readBCFile(file);

    if (!help::for_build::validBCFile(file))
        help::logger::exitWithError("[err] Not a valid buildc file");

    help::Settings settings;
    help::for_build::configure(file, settings);

    string filename = strtok((char*) settings.mainfile.c_str(), ".");

    stringstream cmd;
    cmd << "./" << filename << ".out";

    system(cmd.str().c_str());
}