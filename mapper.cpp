#include <iostream>
#include <string>
#include<fstream>
#include<sstream>
#include<map>
#include <unistd.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>

using namespace std;

const string FIFO_ADDR="fifo";

int main(int argc, char const *argv[])
{
    int fd;
    char file_number[10];
    read(STDIN_FILENO,file_number,1);
    string fn=file_number;
    string file_name="testcases/" + fn + ".csv",temp;
    fstream file;
    file.open(file_name);
    stringstream ss;
    file>>temp;
    ss<<temp;
    file.close();
    cout<<file_name<<endl;
    map<string,int> word_map;
    while(getline(ss,temp,',')){
        if(temp.size()==0){
            continue;
        }
        word_map[temp]=(word_map.count(temp))?word_map[temp]+1:1;
    }
    //cout<<"ok!"<<endl;
    temp="";
    for (auto pair: word_map) {
        temp=temp+pair.first+",";
        //write(fd,temp.c_str(),temp.size());
        temp=temp+to_string(pair.second)+",";
        //write(fd,temp.c_str(),temp.size());
        //cout << "{" << pair.first << ": " << pair.second << "}"<<endl;
    }
    mkfifo(FIFO_ADDR.c_str(),0666);
    if((fd=open(FIFO_ADDR.c_str(),O_RDWR))<0){
        cout<<"error opening pipe"<<endl;
    }
    write(fd,temp.c_str(),temp.size());
    close(fd);
    exit(0);
}
