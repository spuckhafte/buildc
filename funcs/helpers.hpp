#ifndef HELPERS
#define HELPERS

#include <iostream>
#include <sstream>

using namespace std;

namespace help {
    typedef struct Settings {
        string lang;
        string mainfile;
        string compiler;
        stringstream otherfiles;
        stringstream otherdirs;
    } Settings;

    namespace logger {
        void log(string msg);
        void exitWithError(string err);
    }

    namespace for_create {
        const char *newMainFile(string filetype);
        const char *newBuildcFile(string filetype);
        stringstream pathForNewFiles(string dir, string file);
    }

    namespace for_build {
        bool validBCFile(string &file);
        void configure(string &file, Settings &settings);
        void readBCFile(string &file);
        void includeFilesFromDirs(stringstream &cmd, string dir_list, string lang);
    }

    void trim(string &str);
    void helpMsg();
}

#endif