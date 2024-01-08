## BuildC: easy to use build tool for c/c++ projects
(currently supported for linux only)

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
 - run `buildc help` to get the manual
