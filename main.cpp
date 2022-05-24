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
#include<string.h>

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
    int p2[2];
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
    if(pipe(p2)<0){
        cout<<"error making pipe"<<endl;
    }
    if((pid=fork())==0){
        write(p2[1],to_string(i).c_str(),to_string(i).size());
        dup2(p2[1], STDOUT_FILENO);
        dup2(p2[0], STDIN_FILENO);
        execv(REDUCER.c_str(),argv_list_map);
    }
    for(int j=1;j<i;j++){
        if(pipe(p)<0){
            cout<<"error making pipe"<<endl;
        }
        write(p[1],to_string(j).c_str(),to_string(j).size());
        if((pid=fork())==0){
            dup2(p[0], STDIN_FILENO);
            execv(MAPPER.c_str(),argv_list_map);
        }
        close(p[0]);
        close(p[1]);
    }
    for(int j=1;j<=i;j++){
        wait(NULL);
    }

    while(!read(p2[0],output,1024)){
        continue;
    }

    int f1=open("output.csv",O_CREAT|O_RDWR,0666);
    close(f1);
    unlink("output.csv");
    f1=open("output.csv",O_CREAT|O_RDWR,0666);
    write(f1,output,strlen(output));
    close(f1);
    close(p[0]);
    close(p[1]);
    close(p2[0]);
    close(p2[1]);
    exit(0);
}
