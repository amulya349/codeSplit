
void file_gen(string filName)
{
    string funcName; // string to store a line in file and the name of the function ( used to name the generated file)
    fstream fin;
    ofstream foo;
    int pos = filName.find('.');
    string filName2 = filName.substr(0, pos);
    string filHead = "#include \"";    //Here's got a prob.. this line tries to add before the file is opened. so no addition
    filHead +=filName;
    filHead +="\"";
    fin.open(filName.c_str(), ios::in);
    int flag=0; //this variable flags the no of curly brackets
    while (!fin.eof())
    {
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
                    n++;
                    funcName=tokens[i].substr(0,pos);
                    break;
                   }
                }
                funcName=filName2+"."+funcName+".txt"; // the extension of the generated file

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
    }
    fin.close();
    fout.close();
}
