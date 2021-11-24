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
#include <chrono>
#include <thread>


using namespace std;

const string FIFO_ADDR="fifo";

int main(int argc, char const *argv[])
{
    int fd;
    map<string,int> word_map;
    string out,count,temp;
    stringstream ss;
    char fdout[512];
    int i=0;

    if((fd=open(FIFO_ADDR.c_str(),O_RDWR))<0){
        cerr<<"error opening pipe"<<endl;
    }
    usleep(3*100000);
    while(read(fd,fdout,512)){
        out=fdout;
        ss=stringstream(out);
        while(getline(ss,temp,',')){
            getline(ss,count,',');
            word_map[temp]=(word_map.count(temp))?word_map[temp]+stoi(count):stoi(count);
        }
        break;
    }
    stringstream ss2;
    for (auto pair: word_map) {
        ss2 << pair.first << "," << pair.second<<endl;
    }
    write(STDOUT_FILENO,ss2.str().c_str(),ss2.str().size());
    exit(0);
}
