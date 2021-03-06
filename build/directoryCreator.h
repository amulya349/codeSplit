//directoryCreator.h
#include<dirent.h>
#include <vector>
#ifndef DIRECTORY_CREATOR_H
#define DIRECTORY_CREATOR_H

#define DIRNAME "generated"
//#define MAINCPP "./src/main.cpp"
//#define DELIMITER " "
using namespace std;

class directoryCreator {
    public:
    //function to get the contents of dir and save them to files vector
    int getdir( string dir, vector<string> &files ){
            DIR *dp;
            dirent *dirp;
            if((dp  = opendir(dir.c_str())) == NULL) {
                return 105;
            }

            while ((dirp = readdir(dp)) != NULL ){
                if((strcmp(string(dirp->d_name).c_str(), ".") != 0) && (strcmp(string(dirp->d_name).c_str(), "..") != 0) ){
                    files.push_back(string(dirp->d_name));
                    cout<<string(dirp->d_name)<<endl;
                }
            }
            closedir(dp);
            return 0;
        }

    //function creates the "generated" directory.
    void make_dir( ) {
        char c[256];
        getcwd(c, sizeof(c));
        strcat(c, "\\");
        strcat(c, DIRNAME);
        mkdir(c);
        if (!mkdir(c))
            return;
        cout<<"\nDirectory \"generated\" created successfully!!"<<endl<<endl;
    }
};

#endif
