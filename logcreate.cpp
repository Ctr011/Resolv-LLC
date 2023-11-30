#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <stdio.h>
#include <string>
/*
    website for system time...https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemtime
    the parameters for log file:: https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-systemtime
    specific file locations: https://stackoverflow.com/questions/49508779/how-to-create-a-file-in-a-specific-directory-in-c11
    create directories: https://stackoverflow.com/questions/36386036/how-to-create-a-hidden-directory
    find out if there is a directory: https://stackoverflow.com/questions/70924991/check-if-directory-exists-using-filesystem
    find out user profile:: https://stackoverflow.com/questions/42371488/saving-to-userprofile


    Attmepting to Create and Hide Log Files in C:\Users\%USERPROFILE%\AppData\Roaming\ResolvDeckware\
*/
using namespace std;
const int max_char = 255;
void createFile(string n){
    SYSTEMTIME st;
    string year; //container for the to_string command
    string filename = "log";
    string path = "C:/Users/" + n+"/AppData/Roaming/ResolvDeckware/"; //changed directory
    GetSystemTime(&st); //getting system time
    year = to_string(st.wYear); //setting the year
    filename += "_"+ year + ".txt";
    path +=filename;
    ifstream file; //creating ifstream variable to check if file opens

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

void createFolder(string n){ //test system
    string path_dir = "C:/Users/" + n +"/AppData/Roaming/"; //file system we can use
    string  path_folder = "ResolvDeckware"; //folder I want to hide
    string sys_path = path_dir + path_folder; //system path for directory

    if(filesystem::is_directory(sys_path)){ //check if there is a directory 
        cout << "Directory Exists...No need to create directory" << endl;
    } 
    else{ //force check directory
        cout << "there is no directory" << endl;
        cout << "creating directory...please wait..." << endl;
        CreateDirectoryA(sys_path.c_str(),NULL); //create the directory
        SetFileAttributesA(sys_path.c_str(), FILE_ATTRIBUTE_HIDDEN); //make the directory hidden
    }
}

void writingSystem(){
    char userNote[256];
    //string userNote;
    //vector<char> userNote(255);
    int curr = 0;
    cout << "Writing System Test... enter some words" << endl;
    cin.getline(userNote, 256, '\0');
    //cin.read(userNote, 255);
    cout << "The results: " << endl;
    cout << userNote << endl;
    
    /*
    while(curr < max_char){
        cin >> userNote[curr];
        curr++;
    }

    cout << "the results: " << endl;
    cout << userNote << endl;
    */
    
}

string GetUserProfile(){ //changing this to string function
    const char* env_p = getenv("USERPROFILE");
    cout << "Current User Profile: "<<env_p << endl;
    string prof;
    int i = 9;
    while(env_p[i]){ //get the profile
        prof += env_p[i];
        i++;
    }
    cout << "needed profile: " << prof << endl; //Printing out USERPROFILE 
    return prof;
}

int main(){
    cout << "Getting %%USERPROFILE% " << endl;
    GetUserProfile();
    cout << "Testing Folder Creation" << endl;
    createFolder(GetUserProfile());
    cout << "Testing File Creation" << endl;
    createFile(GetUserProfile());
    //cout << "Testing Writing System" << endl;
    //writingSystem();
    return 0;
}