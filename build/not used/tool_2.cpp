#include <iostream>
#include <dirent.h>
#include <unistd.h>
#include <cstring>
#include <conio.h>
#include <vector>
#include <sstream>
#include <iterator>
#include <fstream>
#include <cstring>
#include <vector>
#define DIRNAME "generated"
#define MAINCPP "main.cpp"
#define MAX_CHARS_PER_LINE 512
#define MAX_TOKENS_PER_LINE 20
#define DELIMITER " "
using namespace std;

class direc {
    public:
    //function to get the contents of dir and save them to files vector
	int getdir( string dir, vector<string> &files ){
		DIR *dp;
		dirent *dirp;
		if((dp  = opendir(dir.c_str())) == NULL) {
			return 105;
		}
		while ((dirp = readdir(dp)) != NULL ){
            if((strcmp(string(dirp->d_name).c_str(), ".") != 0) && (strcmp(string(dirp->d_name).c_str(), "..") != 0) )
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
		if (!mkdir(c))
			return;
	}

};

class file {
    void open_file(string filename) {
        fstream myfile;
        myfile.open(filename, ios::in);
    }
    void close_file( fstream myfile) {
        myfile.close();
    }
    void generate_func_file(string fileName, string fileNameShort);



};
void file_gen(string fileName, string fileNameShort);

//main function
int main() {
	cout<<"A Command-line tool to reduce the compile time of c++ programs"<<endl;
	//code to scan the src directory

	vector<string> filesShort = vector<string>();
	direc d;
	d.make_dir();
	d.getdir("./src", filesShort);
	vector<string> files = vector<string>(filesShort.size());
    for(int i=0 ; i< filesShort.size(); i++){
        files[i]= "./src/"+filesShort[i];
        //cout<<files[i]<<endl;
    }
    //file_gen(files[0],filesShort[0]);
    for(int i=0; i<filesShort.size(); i++) {
        if(!files[i].compare(MAINCPP)){
            cout<<"Main found!!"<<endl;
            continue;
        }
        cout<<files[i]<<endl;
        file_gen(files[i], filesShort[i]);
    }


	return 0;

}
void file_gen(string filName, string filNameShort)
{
    string funcName; // string to store a line in file and the name of the function ( used to name the generated file)
    fstream fin;
    ofstream foo;
    int pos = filNameShort.find('.');
    string filName2 = filNameShort.substr(0, pos);
    string filHead = "#include \"";    //Here's got a prob.. this line tries to add before the file is opened. so no addition
    filHead +=filName;
    filHead +="\"";
    fin.open(filName.c_str(), ios::in);
    int flag=0; //this variable flags the no of curly brackets
    cout<<"Running"<<endl;
    while (!fin.eof())
    {
        cout<<"Inside while"<<endl;
        string buf;
        // read an entire line into memory
        getline(fin, buf);
        //Process each line as per conditions
        if(buf.front() != ' '){    //it eliminates lines with class declaration
            continue;
        }
        if(buf.back()== '{'){ // search for the line which ends with '{' i.e. the function definition
            flag++;
            //fout<<buf<<endl;
            if(flag == 1){

                istringstream iss(buf); // parse the line into blank-delimited tokens
                vector<std::string> tokens;
                copy(istream_iterator<string>(iss),istream_iterator<string>(),back_inserter(tokens));
                for (int i = 0; i < tokens.size(); i++) {
                    int pos=tokens[i].find('(');
                   if(pos == string::npos)
                        continue;
                   else{
                    funcName=tokens[i].substr(0,pos);
                    break;
                   }
                }
                funcName="./generated/"+filName2+"."+funcName+".txt"; // the extension of the generated file
                //funcName= "./generated/"+funcName;
                foo.open(funcName.c_str(), ios::out);
                foo<< filHead<<endl;
            }

            foo<<buf<<endl;
            continue;
        }
        if(flag > 0 && buf.back() != '}'){
            //fout<<buf<<endl;
            foo<<buf<<endl;
            continue;
        }
        if(buf.back()== '}'){
            flag--;
            //fout<<buf<<endl;
            foo<<buf<<endl;
            if(flag==0)
                foo.close();
            continue;
        }
        if(fin.eof()== true)
            break;
    }
    fin.close();
}


