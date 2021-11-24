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
    map<string,int> word_map;
    string out,count,temp;
    stringstream ss;
    char fdout[512];

    cout<<"starting!"<<endl;
    if((fd=open(FIFO_ADDR.c_str(),O_RDWR))<0){
        cout<<"error opening pipe"<<endl;
    }
    cout<<read(fd,fdout,512)<<endl;
    out=fdout;
    cout<<out;
    ss<<out;
    while(getline(ss,temp)){
        getline(ss,count);
        word_map[out]=(word_map.count(temp))?word_map[temp]+stoi(count):stoi(count);
        cout<<"o"<<endl;
    }
    for (auto pair: word_map) {
        ss << pair.first << "," << pair.second<<endl;
    }
    write(STDOUT_FILENO,ss.str().c_str(),ss.str().size());
    exit(0);
}
