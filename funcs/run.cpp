#include "run.hpp"

#include <iostream>
#include <filesystem>
#include <string>
#include <sstream>

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

    settings.mainfile.pop_back();
    settings.mainfile.pop_back();
    help::trim(settings.mainfile);

    stringstream cmd;
    cmd << "./" << settings.mainfile << ".out";

    system(cmd.str().c_str());
}