/* A Command line tool to generated files like that happens in java (class wise) so as to speed up compilation process. 
When running this program, put the executable file in the super-directory of src.

Created By: Amulya Kumar Sahoo, IIIT Bhubaneswar, India
Email: amulya349@gmail.com
*/


#include <iostream>
#include <dirent.h>    //Directory related functions
#include <unistd.h>
#include <cstring>
#include <conio.h>    //getch()
#include <vector>
#include <sstream>    //istringstream
#include <iterator>    //istream_iterator
#include <fstream>    //file handling
#include <cstring>
#define DIRNAME "generated"
#define MAINCPP "./src/main.cpp"
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

class file {
    public:
    void generate_func_file(string filName, string filNameShort)
    {
        cout<<endl<<"Processing "<<filNameShort<<endl;
        string funcName; // string to store a line in file and the name of the function ( used to name the generated file)
        fstream fin;
        ofstream foo;
        int pos = filNameShort.find('.');    
        string filName2 = filNameShort.substr(0, pos);
        string filHead = "#include \"";    //This filHead string stores the name of the present file which will be a header for the generated file.
        filHead +=filNameShort;
        filHead +="\"";
        fin.open(filName.c_str(), ios::in);
        int flag=0; //this variable flags the no of curly brackets
        string head=filHead + "\n";    // head string stores the header declarations which are need to be added in the generated files.
 

        /*The below while loop adds the preprocessor declarations of each file. But m having a problem.. When I uncomment the below while
        loop and run the program, it runs with an infinite loop with the follwing while loop ( this loop runs fine). But without the
        below loop, everything runs fine.*/
        /*while(!fin.eof())
        {
            string buf1;
            getline(fin, buf1);
            //cout<<buf1<<endl;
            if(buf1[0]=='#')
            {
                if(buf1[4] == 'l')
                {
                    head+=buf1 + "\n";
                    cout<<head<<endl;
                }
                //continue;
            }
        }
        fin.seekg(0);*/
        //cout<<"Running"<<endl;

        /*When the above loop runs, the below loop runs infinitely. */
        while (!fin.eof())
        {
            //cout<<"Inside while"<<endl;   This line is used for debugging
            string buf;
            // read an entire line into memory
            getline(fin, buf);
            //cout<<buf<<endl;
            //Process each line as per conditions
            if(buf.front() != ' '){    //it eliminates lines with class declaration
                continue;
            }
            if(buf.back()== '{'){ // search for the line which ends with '{' i.e. the function definition
                flag++;
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
                    foo.open(funcName.c_str(), ios::out);
                    foo<<head<<endl;
                }

                foo<<buf<<endl;
                continue;
            }
            if(flag > 0 && buf.back() != '}'){
                foo<<buf<<endl;
                continue;
            }
            if(buf.back()== '}'){
                flag--;
                foo<<buf<<endl;
                if(flag==0)
                    foo.close();
                continue;
            }
        }
        fin.close();
        cout<<"Processed "<<filNameShort<<endl;
    }
    void generate_class_declaration(string filName, string filNameShort)
    {
        fstream fin;
        ofstream foo;
        string fileNameofClass="./generated/"+filNameShort; // the extension of the generated file
        foo.open(fileNameofClass.c_str(), ios::out);
        fin.open(filName.c_str(), ios::in);
        int flag=0; //this variable flags the no of curly brackets
        while (!fin.eof())
        {
            string buf;
            // read an entire line into memory
            getline(fin, buf);
            //Process each line as per conditions
            if(buf.back()== '{'){ // search for the line which ends with '{' i.e. the function definition
                if(buf.front()== ' ')
                    flag++;
                else{
                    foo<<buf<<endl;
                }
                if(flag == 1){
                    int pos = buf.find(')');
                    string funcDecl = buf.substr(0,pos+1);
                    cout<<funcDecl<<endl;
                    funcDecl+=";";
                    foo<<funcDecl<<endl;
                }
                continue;
            }
            else if(flag > 0 && buf.back() != '}'){
                continue;
            }
            else if(buf.back()== '}'){
                flag--;
                continue;
            }
            else
                foo<<buf<<endl;
        }
        fin.close();
        foo.close();
    }
    void copy_main(string filName, string filNameShort)
    {
        cout<<endl<<"Processing "<<filNameShort<<endl;
        string outFile = "./generated/"+filNameShort;
        ifstream fin;
        ofstream fout;
        fin.open(filName.c_str(), ios::in);
        fout.open(outFile.c_str(), ios::out);
        while(!fin.eof()){
            string buf;
            getline(fin, buf);
            fout<<buf<<endl;
        }
        cout<<"Processed "<<filNameShort<<endl;
    }
};

//main function
int main() {
	cout<<"A Command-line tool to reduce the compile time of c++ programs"<<endl<<endl;
	//code to scan the src directory
    file fileObj;
	vector<string> filesShort = vector<string>();
	vector<string> filesGenerated = vector<string>();
	direc d;    //Create an object for directory class
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



