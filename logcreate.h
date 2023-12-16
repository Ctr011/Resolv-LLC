#ifndef LOGCREATE_H
#define LOGCREATE_H

#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <stdio.h>
#include <string>
//#include "./webserver/webserver.cpp"
using namespace std;

/*
    website for system time:: https://learn.microsoft.com/en-us/windows/win32/api/sysinfoapi/nf-sysinfoapi-getsystemtime
    SYSTEMTIME library:: https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-systemtime
    the parameters for log file:: https://learn.microsoft.com/en-us/windows/win32/api/minwinbase/ns-minwinbase-systemtime
    specific file locations:: https://stackoverflow.com/questions/49508779/how-to-create-a-file-in-a-specific-directory-in-c11
    create directories:: https://stackoverflow.com/questions/36386036/how-to-create-a-hidden-directory
    find out if there is a directory:: https://stackoverflow.com/questions/70924991/check-if-directory-exists-using-filesystem
    find out user profile:: https://stackoverflow.com/questions/42371488/saving-to-userprofile


    Attmepting to Create and Hide Log Files in C:\Users\%USERPROFILE%\AppData\Roaming\ResolvDeckware\ && C:\Users\%USERPROFILE%\AppData\Roaming\ResolvBack\

    ATTEMPTING TO CREATE FILES AT DESKTOP:: C:\Users\%USERPROFILE%\Desktop

    Currently debating whether this should turn into a class instead of an instruction file
*/

/*
    Declare Global Variables
*/
const int max_char = 255;
const int max_line = 110;
string path, path_backup;
string filename, file_back;
string month,day; //date
string hour,minute; //time
string date, times;
string year;
string user;
string newMan; //added to make manifest creation easier
string desloc; //added to make manifest creation easier
int conma = 0;

string craneop ="";
bool back = false; //global var to stop system from wasting resources backing up for 1 minute
bool block = false;

/*
    Define Library Functions::
*/
/*
    Information Gathering Functions ::
        These functions gather information that other functions may need.
*/
string GetUserProfile(); //gets %USERPROFILE% var from pc
void DateTime(); //sets date and time when needed
int getTime(); //gets the time for when system is needed

/*
    Program Start Functions::
        These functions run at the start of the program to set up the memory locations for the log
        files
*/
void StartLib(); //calls all of the following functions
void InitialStart(); //initializes all functions
void CreateFile(); //creates needed files. 
void CreateFolder(); //creates hidden directories for log files

/*
    Checking Functions::
        These functions just return true if problems are detected. otherwise can ignore as everything else
        is going fine.
*/
bool CheckRestrictedChars(string n); //checks for restricted characters
bool CheckRestrictedWords(vector<string>&); //checks for restricted words
bool UserLimit(string); //checks if user exceeded 255 character limit

/*
    Update Functions::
        These functions are the update functions for log interactions. Anything that goes into the logs, have to 
        go through here first. Thankfully, they are not difficult to implement and use. 
*/
void UpdateFileM(string); //takes in the manifest when loaded and counts containers
void UpdateFileLogin(string); //takes user login details: signs in and out a user
void WritingSystem(string); //takes the user custom note and puts it into the log file if all parameters are followed
void UpdateContainerLog(string,string); //takes in container name and movement (onloaded or offloaded)
void UpdateBalanceLog(string); //takes in manifest and outputs that the ship was balanced. Special case as there are no specific containers to be modified
void FinalLogUpdate(string); //takes final manifest name created by program and sets up a reminder to user to email it (this can only be seen in the logs)

/*
    Backup solution::
        This function should be called every 30 minutes on the dot, so the logs can be backed up in another directory.
*/
void BackupLogs();
#endif