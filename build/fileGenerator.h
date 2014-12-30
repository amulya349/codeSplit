//fileGenerator.h

#ifndef FILE_GENERATOR_H
#define FILE_GENERATOR_H

class fileGenerator {
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
                    funcName="./generated/"+filName2+"."+funcName+".cpp"; // the extension of the generated file
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
#endif // FILE_GENERATOR_H
