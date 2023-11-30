#include <iostream>
#include <fstream>
#include <Windows.h>
#include <filesystem>
#include <stdio.h>
#include <string>
/*
    website for system time...https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemtime
    the parameters for log file:: https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-systemtime
    specific file locations: https://stackoverflow.com/questions/49508779/how-to-create-a-file-in-a-specific-directory-in-c11
    create directories: https://stackoverflow.com/questions/36386036/how-to-create-a-hidden-directory
    find out if there is a directory: https://stackoverflow.com/questions/70924991/check-if-directory-exists-using-filesystem
*/
using namespace std;

void createFile(){
    SYSTEMTIME st;
    string year; //container for the to_string command
    string filename = "log";
    string path = "C:/Users/Public/Documents/";
    GetSystemTime(&st); //getting system time
    year = to_string(st.wYear); //setting the year
    filename += "_"+ year + ".txt";
    path +=filename;
    ifstream file; //creating open to open file

    file.open(path);

    

    if(file){ //we are checking to see if the file is created
        cout << "File Exists...No need to create file..." << endl;
    }
    else{ //file does not exist, we create the file
        cout << "File Non-Existent...Creating File..." << endl;
        ofstream outfile(path);

        outfile << "File Creation Success!!" << endl;

        outfile.close();
    }


}

void createFolder(){ //test system
    string path_dir = "C:/Users/Public/Documents/"; //file system we can use
    string  path_folder = "appData"; //folder I want to hide
    string sys_path = path_dir + path_folder; //system path for directory
    CreateDirectoryA(sys_path.c_str(),NULL); //create the directory
    SetFileAttributesA(sys_path.c_str(), FILE_ATTRIBUTE_HIDDEN); //make the directory hidden
    if(filesystem::is_directory(sys_path)){ //check if there is a directory 
        cout << "directory is here" << endl;
    }
    else{
        cout << "there is no directory" << endl;
    }
}

int main(){
    createFile();
    createFolder();
    return 0;
}
