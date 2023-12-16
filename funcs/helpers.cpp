#include "helpers.hpp"

#include <iostream>
#include <sstream>
#include <cstring>
#include <filesystem>

using namespace std;
namespace fs = filesystem;

namespace help
{
    void trim(string &str)
    {
        while (str.front() == ' ')
            str.erase(0, 1);
        while (str.back() == ' ')
            str.pop_back();
    }

    namespace logger
    {
        void log(string msg)
        {
            cout << endl
                 << msg << endl
                 << endl;
        }

        void exitWithError(string err)
        {
            log(err);
            exit(1);
        }
    }

    namespace for_create
    {
        const char *newMainFile(string filetype)
        {
            if (filetype == "c")
                return "#include <stdio.h>\n\nint main() {\n    printf(\"Hello World\\n\");\n\n    return 0;\n}";
            else
                return "#include <iostream>\n\nint main() {\n    std::cout << \"Hello World\\n\";\n\n    return 0;\n}";
        }

        const char *newBuildcFile(string filetype)
        {
            if (filetype == "c")
                return "lang: c\ncompiler: gcc\nmainfile: main.c\nother-files: \nother-dirs: ";
            else
                return "lang: cpp\ncompiler: g++\nmainfile: main.cpp\nother-files: \nother-dirs: ";
        }

        stringstream pathForNewFiles(string dir, string file)
        {
            stringstream ss;
            if (dir != ".")
                ss << "./";
            ss << dir << "/" << file;
            return ss;
        }
    }

    namespace for_build
    {
        void configure(string &file, Settings &settings)
        {
            string forLang = strtok((char *)file.c_str(), "\n");
            string forComp = strtok(NULL, "\n");
            string forMain = strtok(NULL, "\n");
            string forOthr = strtok(NULL, "\n");
            string forDirs = strtok(NULL, "\n");

            strtok((char *)forLang.c_str(), ": ");
            settings.lang = strtok(NULL, ": ");

            strtok((char *)forComp.c_str(), ": ");
            settings.compiler = strtok(NULL, ": ");

            strtok((char *)forMain.c_str(), ": ");
            settings.mainfile = strtok(NULL, ": ");

            strtok((char *)forOthr.c_str(), ":");
            settings.otherfiles << strtok(NULL, ":");

            strtok((char *)forDirs.c_str(), ":");
            settings.otherdirs << strtok(NULL, ":");
        }

        bool validBCFile(string &file)
        {
            string tokens[5] = {"lang:", "mainfile:", "compiler:", "other-files:", "other-dirs:"};

            for (const string &token : tokens)
                if (file.find(token) == string::npos)
                    return false;

            return true;
        }

        void readBCFile(string &str)
        {
            FILE *fp;
            fp = fopen("buildc", "r");

            int c = fgetc(fp);
            char ch[1];
            while (c != EOF)
            {
                ch[0] = (char)c;
                str.append(ch);
                c = fgetc(fp);
            }
        }

        void includeFilesFromDirs(stringstream &cmd, string dir_list, string lang)
        {
            stringstream path;

            for (auto &dir : fs::directory_iterator("."))
            {
                string dirname = dir.path();
                dirname.erase(0, 2);

                if (dir_list.find(dirname) != string::npos)
                {
                    lang.insert(lang.begin(), '.');

                    for (auto &file : fs::directory_iterator(dir.path()))
                        if (file.path().string().find(lang) != string::npos)
                            cmd << " " << file.path().string() << " ";
                }
            }
        }
    }

    void helpMsg() {
        stringstream msg;
        msg << "BuildC: easy to use build tool for c/c++ projects\n"
        << "\ncommands: create, build, run\n"

        << "[create]:\n"
        << "\t> buildc create <project_name> <project_lang>\n"
        << "\t\"project_name\": name of the new dir that will contain the project, use (.) to set the current dir as project dir\n"
        << "\t\"project_lang\": language for the project: c | cpp\n"
        << "\n\tThis cmd will create a new project with a default environment, a main file and a buildc file (explained later)\n"
        
        << "\n[build]:\n"
        << "\t> buildc build\n"
        << "\n\tWill compile all the files including main and others, as specified in the buildc file\n"
        
        << "\n[run]:\n"
        << "\t> buildc run\n"
        << "\n\tWill run the compiled executable\n"

        << "\nThe [buildc] file:\n"
        << "\tThis file contains the information of the project including the language, compiler, mainfile, other_files and other_dirs\n"
        << "\tother_files: files specfied in this field gets included in the final compile command\n"
        << "\tother_dirs: all the .c/.cpp files present in the specified directory gets included in the final compile command\n"
        << "\nAn example for a [buildc] file (c project):\n"
        << "\n\tlang: c\n\tcompiler: gcc\n\tmainfile: main.c\n\tother-files: file1.c file2.c\n\tother-dirs: dir1 dir2\n"
        << "\n(by default, other-files and other-dirs fields are empty)\n"
        << "NOTE: the order of the fields should not be altered from the one provided by the [create] cmd";

        help::logger::log(msg.str());
    }
}