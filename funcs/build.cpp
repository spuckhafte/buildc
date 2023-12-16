#include "build.hpp"

#include <iostream>
#include <string>
#include <filesystem>

#include "helpers.hpp"

using namespace std;
namespace fs = filesystem;

void build() {
    if (!fs::exists("buildc") || fs::is_empty("buildc"))
        help::logger::exitWithError("[err] Not a BuildC project");

    string file;
    help::for_build::readBCFile(file);

    if (!help::for_build::validBCFile(file))
        help::logger::exitWithError("[err] Not a valid buildc file");

    help::Settings settings;
    help::for_build::configure(file, settings);

    stringstream cmd;
    cmd << settings.compiler << " " << settings.mainfile << " " << settings.otherfiles.str();

    help::for_build::includeFilesFromDirs(cmd, settings.otherdirs.str(), settings.lang);

    settings.mainfile.pop_back();
    settings.mainfile.pop_back();
    help::trim(settings.mainfile);
    cmd << " -o " << settings.mainfile << ".out";

    int status = system(cmd.str().c_str());

    if (status == 0)
        help::logger::log("Build Successfull!\n\tuse: buildc run");
}