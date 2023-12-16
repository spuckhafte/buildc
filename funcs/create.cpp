#include "create.hpp"

#include <iostream>
#include <string>
#include <filesystem>
#include <fstream>
#include <sstream>

#include "helpers.hpp"

using namespace std;
namespace fs = filesystem;

void create(string projectname, string projectlang) {
    ostringstream ss;

    if (projectlang != "c" && projectlang != "cpp")
        help::logger::exitWithError("[Err]: Project lang can only be c/cpp");

    if (projectname == "." && !fs::is_empty(fs::current_path())) 
        help::logger::exitWithError("[Err]: current directory is not empty");

    if (projectname != ".") {
        if (fs::exists(projectname)) 
            help::logger::exitWithError("[Err]: this projects already exists");

        fs::create_directory(projectname);
    }

    string mainfile_name("main.");
    mainfile_name.append(projectlang);

    ofstream mainfile(help::for_create::pathForNewFiles(projectname, mainfile_name).str());
    mainfile << help::for_create::newMainFile(projectlang);

    ofstream buildcfile(help::for_create::pathForNewFiles(projectname, "buildc").str());
    buildcfile << help::for_create::newBuildcFile(projectlang);

    help::logger::log("Created project successfully!");
}