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

int main(int argc, char const *argv[])
{
    int fd;
    char file_number[10];
    read(STDIN_FILENO,file_number,10);
    string fn=file_number;
    string FIFO_ADDR="tmp/fifo"+fn;
    string file_name="testcases/" + fn + ".csv",temp;
    fstream file;
    file.open(file_name);
    stringstream ss;
    file>>temp;
    ss<<temp;
    file.close();
    map<string,int> word_map;
    ss<<",";
    while(getline(ss,temp,',')){
        if(temp.size()==0){
            continue;
        }
        word_map[temp]=(word_map.count(temp))?word_map[temp]+1:1;
        if(ss.str().size()==0){
            break;
        }
    }
    temp="";
    for (auto pair: word_map) {
        temp=temp+pair.first+",";
        temp=temp+to_string(pair.second)+",";
    }
    temp+='\0';
    mkfifo(FIFO_ADDR.c_str(),S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
    if((fd=open(FIFO_ADDR.c_str(),O_WRONLY))<0){
        cout<<"error opening pipe"<<endl;
    }
    write(fd,temp.c_str(),temp.size());
    close(fd);
    exit(0);
}
