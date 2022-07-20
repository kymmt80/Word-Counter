#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <map>
#include <unistd.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <chrono>
#include <thread>
#include <vector>

using namespace std;

int main(int argc, char const *argv[])
{
    int fcount;
    char file_count[10];
    string FIFO_ADDR = "tmp/fifo";
    map<string, int> word_map;
    string out, count, temp;
    stringstream ss;
    char fdout[10000];
    int i = 0;
    vector<int>fd;
    read(STDIN_FILENO, file_count, 1);
    fcount = (stoi(string(file_count)));
     for (int j = 1; j < fcount; j++)
    {
        mkfifo(string(FIFO_ADDR+to_string(j)).c_str(),S_IWUSR | S_IRUSR | S_IRGRP | S_IROTH);
        fd.push_back(open(string(FIFO_ADDR+to_string(j)).c_str(), O_RDONLY));
        if ((fd[j-1]) < 0)
        {
            cerr << "error opening pipe" << endl;
        }
    }
    for (int j = 1; j < fcount; j++)
    {
        read(fd[j-1], fdout, 10000);
        out = fdout;
        ss = stringstream(out);
        while (getline(ss, temp, ','))
        {
            i++;
        }
        ss = stringstream(out);
        while (getline(ss, temp, ','))
        {
            getline(ss, count, ',');
            word_map[temp] = (word_map.count(temp)) ? word_map[temp] + stoi(count) : stoi(count);
            i--;
            if (i <= 1)
            {
                break;
            }
        }
        close(fd[j-1]);
    }
    stringstream ss2;
    for (auto pair : word_map)
    {
        ss2 << pair.first << "," << pair.second << endl;
    }
    ss2<<'\0';
    write(STDOUT_FILENO, ss2.str().c_str(), ss2.str().size());
    exit(0);
}
