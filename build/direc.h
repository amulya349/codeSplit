#ifndef DIREC_H
#define DIREC_H

#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <vector>
#define DIRNAME "generated"

class direc {
	int getdir( string dir, vector<string> &files ){
		DIR *dp;
		dirent *dirp;
		if((dp  = opendir(dir)) == NULL) {
			//cout << "Error(" << errno << ") opening " << dir << endl;
			return 105;
		}
		while ((dirp = readdir(dp)) != NULL ){
			files.push_back(string(dirp->d_name));
		}
		closedir(dp);
		return 0;
	}
	void make_dir( ) {
		char c[256];
		getcwd(c, sizeof(c));
		strcat(c, "\\");
		strcat(c, DIRNAME);
		mkdir(c);
		/*if (!mkdir(c))
			cout<<"Error... Unable to create generate directory!!"<<endl;*/
	}

}



#endif
