#include <iostream>
#include <string>
#include<sstream>
#include<map>
#include <unistd.h>
#include <filesystem>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include<fstream>

using namespace std;

const string MAPPER="mapper";
const string REDUCER="reducer";
const string FIFO_ADDR="tmp/fifo";

int main(int argc, char const *argv[])
{
    string addr=FIFO_ADDR;
    int i=1,pid;
    char * argv_list_map[] = {"mapper","tmp/fifo",NULL};
    int p[2];
    char output[1024];
    string file_name;
    string res;
    while(true){
        file_name="testcases/" + to_string(i) + ".csv";
        if (FILE *file = fopen(file_name.c_str(), "r")) {
            fclose(file);
            i++;
            continue;
        }
        break;
    }
    if(pipe(p)<0){
        cout<<"error making pipe"<<endl;
    }
    for(int j=1;j<i;j++){
        file_name="testcases/" + to_string(j) + ".csv";
        write(p[1],to_string(j).c_str(),to_string(j).size());
        if((pid=fork())==0){
            dup2(p[0], STDIN_FILENO);
            execv(MAPPER.c_str(),argv_list_map);
        }
    }
    for(int j=1;j<i;j++){
        cout<<j<<endl;
        wait(NULL);
    }

    cout<<"part1 complete"<<endl;
    if((pid=fork())==0){
        //dup2(p[1], STDOUT_FILENO);
        cout<<"please"<<endl;
        execv(REDUCER.c_str(),argv_list_map);
    }
    cout<<"waiting"<<endl;
    wait(NULL);
    while(!read(p[0],output,1024)){
        continue;
    }
    res=output;
    cout<<output;
    fstream fres("output.csv");
    fres<<res;
    exit(0);
}
