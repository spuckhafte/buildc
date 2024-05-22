#include "funcs/create.hpp"
#include "funcs/build.hpp"
#include "funcs/helpers.hpp"
#include "funcs/run.hpp"


int main(int args_c, char* args[]) {
    if (args_c < 2) {
        help::logger::exitWithError("[err] No such command available\n\tuse: buildc help");
    }

    string cmd(args[1]);

    if (cmd == "create") { 
        if (args_c != 4) 
            help::logger::exitWithError("[err] Wrong cmd\n\t> buildc create <project_name> <project_lang: c|cpp>");
        create(args[2], args[3]);
    }

    else if (cmd == "build")
        build();

    else if (cmd == "run")
        run();

    else if (cmd == "help")
        help::helpMsg();

    else if (cmd == "try") {
        build();
        run();
    }


    else
        help::logger::exitWithError("[err] No such command available\n\tuse: buildc help");



    return 0;
}
