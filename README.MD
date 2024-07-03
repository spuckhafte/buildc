## BuildC: easy to use build tool for c/c++ projects
BuildC is a lightweight and user-friendly build tool for C/C++ projects, simplifying project creation, compilation, and execution with its intuitive command-line interface. With automated compilation and customizable configuration, BuildC streamlines the development process, allowing developers to focus on coding rather than managing build commands.

*(currently supported for **linux** only)*

### How to use:
 - open terminal
 - run this cmd
 *(using svn: sudo apt install svn)*
 ```bash
 sudo svn export https://github.com/spuckhafte/buildc/trunk/extract-buildc && sh extract-buildc && sudo rm extract-buildc
 ```
 *(or)*
 ```
 git clone https://github.com/spuckhafte/buildc && sudo mv ./buildc/extract-buildc ./ && sudo rm -r buildc && sh extract-buildc && rm extract-buildc
 ```
if the above 2 doesn't work for some reason, build it:
```
1. git clone https://github.com/spuckhafte/buildc
2. cd buildc
3. rm -r buildc
3. g++ main.cpp ./funcs/build.cpp ./funcs/create.cpp ./funcs/helpers.cpp ./funcs/run.cpp -o buildc
4. sudo mv buildc ../../../bin
5. cd ../ && rm -r buildc
```
 - run `buildc help` to get the manual
