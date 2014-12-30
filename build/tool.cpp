/* A Command line tool to generated files like that happens in java (class wise) so as to speed up compilation process.
When running this program, put the executable file in the super-directory of src.

Created By: Amulya Kumar Sahoo, IIIT Bhubaneswar, India
Email: amulya349@gmail.com
*/


#include <iostream>
#include <unistd.h>
#include <cstring>
#include <conio.h>    //getch()
#include <vector>
#include <sstream>    //istringstream
#include <iterator>    //istream_iterator
#include <fstream>    //file handling
#include <cstring>
#include "directoryCreator.h"
#include "fileGenerator.h"
#define MAINCPP "./src/main.cpp"
#define DELIMITER " "
using namespace std;

//main function
int main() {
	cout<<"A Command-line tool to reduce the compile time of c++ programs"<<endl<<endl;
	//code to scan the src directory
    fileGenerator fileObj;
	vector<string> filesShort = vector<string>();
	vector<string> filesGenerated = vector<string>();
	directoryCreator d;    //Create an object for directory class
	cout<<"Directory .\\src found and opened successfully !!"<<endl<<endl;
	cout<<"Following files are found:"<<endl;
	d.getdir("./src", filesShort);
	d.make_dir();    //make the generated directory
	vector<string> files = vector<string>(filesShort.size());
    for(int i=0 ; i< filesShort.size(); i++){
        files[i]= "./src/"+filesShort[i];
    }
    for(int i=0; i<filesShort.size(); i++) {
        if(!files[i].compare(MAINCPP)){
            fileObj.copy_main(files[i], filesShort[i]);
            continue;
        }
        //cout<<files[i]<<endl;
        fileObj.generate_func_file(files[i], filesShort[i]);
        fileObj.generate_class_declaration(files[i], filesShort[i]);
    }
    cout<<"\nList of generated files:\n";
    d.getdir("./generated", filesGenerated);
	return 0;
}



