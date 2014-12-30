#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include <sstream>
#include <iterator>
#define MAX_CHARS_PER_LINE 512
#define MAX_TOKENS_PER_LINE 20
#define DELIMITER " "
using namespace std;
int main ()
{
        fstream fin;
        ofstream foo;
        string filName = "RandGenAnsi.h";
        string filNameShort = filName;
        string fileNameofClass=filNameShort+".txt"; // the extension of the generated file
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
                //fout<<buf<<endl;
                //foo<<buf<<endl;
                continue;
            }
            else
                foo<<buf<<endl;
        }
        fin.close();
        foo.close();
    }
