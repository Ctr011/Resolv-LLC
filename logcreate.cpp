#ifndef LOGCREATE_CPP
#define LOGCREATE_CPP
#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <stdio.h>
#include <string>
#include "logcreate.h"
//#include "./webserver/webserver.cpp"
using namespace std;


string GetUserProfile(){ //changing this to string function from void
    const char* env_p = getenv("USERPROFILE"); //checks user system for path
    //cout << "Current User Profile: "<<env_p << endl;
    string prof; //store the user profile
    int i = 9; //start array at start of user file
    while(env_p[i]){ //get the profile
        prof += env_p[i]; //store user file
        i++;//iterate
    }
    cout << "needed profile: " << prof << endl; //Printing out USERPROFILE 
    return prof; //user profile here
}

/*
    Year Prameter assumes that the system will be turned off during the new year and be ran when needed. 
    ALL FUNCTIONS SHOULD RUN ON PROGRAM RESET 
*/

void InitialStart(){ //initial start.
    cout << "Getting %%USERPROFILE% " << endl; //initial statement
    user = GetUserProfile(); //call system info
    SYSTEMTIME st; //enter in system time
    filename = "log"; //original log file
    file_back = "log"; //backup log file
    path = "C:/Users/" + user+"/AppData/Roaming/ResolvDeckware/"; //current directory, user is obtained from GetUserProfile()
    path_backup = "C:/Users/" + user+"/AppData/Roaming/ResolvBack/"; //current backup directory, user is obtained from GetUserProfile()
    desloc = "C:/Users/" + user+ "/Desktop/";
    GetLocalTime(&st); //getting system time
    year = to_string(st.wYear); //setting the year
    filename += "_"+ year + ".txt"; //full file name
    file_back += "_" + year + "_backup.txt"; //full backup name
    path +=filename; //original file path
    path_backup += file_back; //backup file path
}

void DateTime(){
    SYSTEMTIME st;
    GetLocalTime(&st);

    if(st.wMonth < 10){month = "0"; month += to_string(st.wMonth);}
    else {month = to_string(st.wMonth);}
    if(st.wDay < 10){day = "0"; day+= to_string(st.wDay);}
    else {day = to_string(st.wDay);}
    if(st.wHour < 10){hour = "0"; hour += to_string(st.wHour);}
    else {hour = to_string(st.wHour);}
    if(st.wMinute < 10){minute = "0"; minute += to_string(st.wMinute);}
    else{minute = to_string(st.wMinute);}
    date = month +"/"+day+"/"+year;
    times = hour +":" + minute;
}

/*
    current system is working under the assumption that the system continues
    working throughout the day none stop. If program stops right before hour changes 
    or half-past the hour, we will have to wait for the next 30 minutes. Can change the 
    intervals to every 15 minutes if needed. 
*/
int getTime(){
    SYSTEMTIME st; //system to let the backup system work
    GetSystemTime(&st); 
    return st.wMinute; //using minutes
}
void CreateFile(){
    bool bFile = false; //not necessary
    bool oFile = false; //not necessary

    ifstream file; //creating ifstream variable to check if file opens
    ifstream b_file; //creating backup file

    file.open(path);
    if(file){ //we are checking to see if the file is created
        cout << "File Exists...No need to create file..." << endl; //just showing that file exists
        oFile = true;
    }
    else{ //file does not exist, we create the file
        cout << "File Non-Existent...Creating File..." << endl; //result of file not being here...indication of new file creation
        ofstream outfile(path);
        //outfile << "File Creation Success!!" << endl;
        cout << "Original Log File Has Been Created..." << endl;
        outfile.close();
    }

    b_file.open(path_backup);
    if(b_file){ //checking if there is a backup system
        cout << "File Exists...No need to create file..." << endl; //indication that there is already a file, in case system resets randomly. 
        bFile = true;
    }
    else{
       //cout << "File Non-Existent...Creating File..." << endl;
        ofstream offFile(path_backup); //create file if none there
        //offFile << "File Creation Success!!" << endl;
        cout << "Backup Log File Has Been Created..." << endl;
        offFile.close();
    }

    /*
        This next part of the code can be commented out, not needed for anything other than testing.
        This test is meant for rerun programs. 
    */
    if(bFile && oFile){cout << "Both Files Were Created!!" << endl;}
    else{cout << "We are missing one or both files..." << endl;
        cout << "Re-run test to see if they were created..." << endl;} //checking if the files were created

}

/*
    Current iteration does not allow for password protected libraries for the user. Currently, looking through serveral
    windows/file/system libraries to figure out any system to add this feature. 
    FUTURE INTERATIONS NEED TO INCLUDE PASSWORD OR ENCRYPTION OF DIRECTORY
*/
void CreateFolder(){ //test system
    string path_dir = "C:/Users/" + user +"/AppData/Roaming/"; //file system we can use
    string  path_folder = "ResolvDeckware"; //folder I want to hide
    string backup_folder = "ResolvBack"; //backup folder I want to hide
    string hidden_selection = "userhide";//hiddent selection from js
    string sys_path = path_dir + path_folder; //system path for directory
    string sys_back = path_dir + backup_folder; //backup path 
    string sys_user = path_dir + hidden_selection;

    /*
        could seperate systems if needed...
    */
    if(filesystem::is_directory(sys_path) && filesystem::is_directory(sys_back)){ //check if there is a directory for both normal and backup
        cout << "Directory Exists...No need to create directory" << endl; //DEV results
    } 
    else{ //force check directory
        cout << "there is no directory" << endl; //dev results
        cout << "creating directory...please wait..." << endl; //indicating new directories will be created
        CreateDirectoryA(sys_path.c_str(),NULL); //create the directory
        SetFileAttributesA(sys_path.c_str(), FILE_ATTRIBUTE_HIDDEN); //make the directory hidden

        cout << "creating backup directory...please wait " << endl;
        CreateDirectoryA(sys_back.c_str(),NULL); //create the directory
        SetFileAttributesA(sys_back.c_str(), FILE_ATTRIBUTE_HIDDEN); //make the directory hidden
    }
}

bool CheckRestrictedChars(string n){ //checks for characters outside the ACII rating of
    printf("TEST HAS HIT CHARACTER RESTRICTION FUNCTION\n");
    int i = 0;
    string name;
    if(n.size() == 1){ //if size of user input is 1, we check if its just a space...considered empty string
        if(n.at(i) == ' '){return true;}
        if(n.empty()){return true;}
    }
    if(n.size() == 0){return true;}
    while(n[i]){ //function which goes through entire user input
        if(int(n[i]) < 32 || int(n[i]) > 126 ){
            return true;
        }
        i++;
    }
    return false; //No Restricted Character was found
}

/*
    Following function is just a safe-guard for the log file input. There should be no reason to 
    use it, but better safe than sorry.
*/
bool CheckRestrictedWords(vector<string> &n){ //checks for the restricted words
    printf("TEST HAS HIT WORD RESTRICTION FUNCTION\n");
    for(int i = 0; i < n.size(); i++){
        if(n.at(i) == "UNUSED"){return true;} //exits when UNUSED is detected
        if(n.at(i) == "NAN"){return true;} //exists when NAN is detected
    }
    return false; //No Restricted Word was found
}

/*
    Following function is just a safe-guard for the log file input. There should be no reason to 
    use it, but better safe than sorry.
*/
bool UserLimit(string c){ //takes user input
    if(c.size() > max_char){ //checks if user input is bigger than max character count
        return true;} //return true if characters are exeeded
    return false; //returns false if character limit is less or equal to max character count
}

void UpdateFileM(string manifestName){//designed for initial and ending
    printf("INITIAL TEST FOR MANIFEST FILE...\n");
    //cout << manifestName << endl; //checking to see if manifest is correct, backend system
    for(int i = 0; i < manifest.size(); i++){
        if(manifest.at(i) != '.'){
            newMan += manifest.at(i); //adding initial parts of the name, assuming first part of manifest is the ship name
        }
        else if(manifest.at(i) == '.' && manifest.at(i+1) == 't' && manifest.at(i+2) == 'x' && manifest.at(i+3) == 't'){ //checking the next few characters
            i = manifest.size();}
    }

    DateTime(); //set time and date
    ofstream file;
    file.open(path , ios_base::app); //open file in append mode to not delete old files
    if(file){ //check if we have a log file
            printf("SYSTEM HAS DETECTED LOG FILE...ATTEMPTING TO LOAD MANIFEST INTO LOG...\n");
            // newMan = manifestName;
            file << date << ": " << times;
            file << " ";//Here should be 19 characters, we want lines of 
            file << "Manifest " << manifestName << " is opened, there are "; //place in manifest file
            file << to_string(conma) <<" containers on the ship"; //output the container count when loaded
            file << "\n";
            conma = 0; //reset count
            block = false; //reset block feature for initial check
     }
    else{printf("SYSTEM IS NOT DETECTING THE LOG FILE CURRENTLY...\n");}
    file.close(); //close the file to free resources.

    return;
}

void UpdateFileLogin(string userlogging){ //deisgned for user login
    vector<string> containerCheck;
    string input ="";//checking name if is correct format (UNUSABLE CHARACTERS AND CHARACTER LIMIT)
    
    if(UserLimit(userlogging)){ //check if user input exceeds max character limit
        printf("SYSTEM ERROR...CHARACTER LIMIT EXCEEDED...FORCING EXIT...\n"); //backend error
        return;}    //checking if user is puttin

    // cout << n.size() << endl;
    // cout << n << endl;
    for(int i = 0; i < userlogging.size(); i++){ //sets up the vector for checking 
        if(userlogging.at(i) != ' '){
            input += userlogging.at(i);    
            // cout << input<< endl;
            if(i+1 >= userlogging.size()){//fixed issue where input was not getting final word
                containerCheck.push_back(input);}
             }
        else{
            // cout << input << endl;
            containerCheck.push_back(input);
            input ="";
        }}

    if(CheckRestrictedChars(userlogging) ) {//checking for Restricted Characters
        printf("System Detected Restricted Character...Forcing EXIT... \n"); //backend error
        return;} //error out
    if(CheckRestrictedWords(containerCheck)) { //checking for restricted words
        printf("System Detected Restricted Words...Forcing Exit... \n");
        return;} //error out

    DateTime(); //get time and date
    ofstream file;
    file.open(path , ios_base::app); //open file in append mode
    if(file){//check if we have a log file
        if(craneop == ""){//System Restarted, now there is no crane op logged in
            printf("SYSTEM CANNOT DETECT PREVIOUS OP LOGIN...SIGNING IN NEW OP...\n"); //can also be that this is the first time the system turns on
            cout << "USER SIZE: " << userlogging.size() << endl;
            file << date << ": " << times;
            file << " ";//Here should be 19 characters, we want lines of 
            file << userlogging << " signs in" << "\n"; //first user log in

        }
        else if(craneop != userlogging){
            printf("SYSTEM DETECTED NEW OPERATOR LOGIN...SIGNING OUT PREVIOUS OP...\n");
            file << date << ": " << times;
            file << " ";//Here should be 19 characters, we want lines of 
            file << craneop << " signs out" << "\n";
            file << date << ": " << times;
            file << " ";//Here should be 19 characters, we want lines of 
            file << userlogging << " signs in" << "\n";


     }
     craneop = userlogging; //setting current operator to the one passing through the system
     cout << "craneop: " << craneop << endl;
    }
    else{printf("SYSTEM IS NOT DETECTING THE LOG FILE CURRENTLY...\n");} 
    file.close(); //free the file
    return;
}

void WritingSystem(string n){ //for parsing user input to file
    vector<string> containerCheck;
    string input=""; //setting input container to null
    printf("SYSTEM HAS DETECTED USER INPUT...\n");

    if(UserLimit(n)){ //check if user input exceeds max character limit
        printf("SYSTEM ERROR...CHARACTER LIMIT EXCEEDED...FORCING EXIT...\n"); //backend error
        return;}    

    // cout << n.size() << endl;
    // cout << n << endl;
    for(int i = 0; i < n.size(); i++){ //sets up the vector for checking 
        if(n.at(i) != ' '){
            input += n.at(i);    
            // cout << input<< endl;
            if(i+1 >= n.size()){//fixed issue where input was not getting final word
                containerCheck.push_back(input);}
             }
        else{
            // cout << input << endl;
            containerCheck.push_back(input);
            input ="";
        }
    }

    if(CheckRestrictedChars(n) ) {//checking for Restricted Characters
        printf("System Detected Restricted Character...Forcing EXIT... \n"); //backend error
        return;} //error out
    if(CheckRestrictedWords(containerCheck)) { //checking for restricted words
        printf("System Detected Restricted Words...Forcing Exit... \n");
        return;} //error out

    /*
        Setting all variables with their data. Since most will be pushed to txt file, we
        need to create strings out of all time variables. Additional help needed to add "0"
        to comply with MM/DD/YYYY format
    */

    DateTime();  //get date and time
    ofstream file;
    file.open(path, ios_base::app); //File opens in append mode
    if(file){
        int cnt = 19;
        file << date << ": " << times;
        file << " ";//Here should be 19 characters, we want lines of 
        int i = 0;
        while(containerCheck.size() > i){ //we want to do lines of 110 characters 
            cnt += containerCheck.at(i).size()+1; //setting size for cnt
            if(cnt <= max_line){ //checking if current line cnt is fine
                file << containerCheck.at(i); //put words if its alright
                file << " ";
            }
            else{ //go down a line when a word reaches the 110 character line
                file << "\n" << containerCheck.at(i); 
                file << " ";
                cnt = containerCheck.at(i).size()+1; 
            }
            i++;
        }
        file << '\n';
    }
    else{printf("SYSTEM ERROR...FILE DOES NOT EXIST...\n");} //backend error
    file.close(); //free file
    return;
} 

void UpdateContainerLog(string cont, string movs){//has three options onload and offload
    printf("SYSTEM HAS DETECTED CONTAINER MOVEMENT\n");
    DateTime(); //get time and date
    //printf("INITIAL TEST FOR CONTAINER LOGS...\n");

    ofstream file;
    file.open(path, ios_base::app); //open file in append mode
    if(file){
        file << date << ": " << time;
        file << " ";//Here should be 19 characters, we want lines of 
        file << "\"" << cont << "\" is " << movs << endl;
    }
    else {printf("SYSTEM CANNOT DETECT LOG FILE...\n");}
    file.close(); //free file
}

void UpdateBalanceLog(string manifest){//we will get the ship name from manifest, though we can just say that the manifest was balanced
    printf("SYSTEM HAS DETECTED SOME SORT OF BALANCE OF SHIP\n");
    DateTime(); //get date and time
    string ship =""; //creating container for name
    for(int i = 0; i < manifest.size(); i++){
        if(manifest.at(i) != '.'){
            ship += manifest.at(i); //adding initial parts of the name, assuming first part of manifest is the ship name
        }
        else if(manifest.at(i) == '.' && manifest.at(i+1) == 't' && manifest.at(i+2) == 'x' && manifest.at(i+3) == 't'){ //checking the next few characters
            i = manifest.size();
        }
    }

    ofstream file;
    file.open(path, ios_base::app);
    if(file){ //we might not need to have a input
        file << date << ": " << time;
        file << " ";//Here should be 19 characters, we want lines of 
        
        // if(baltype == "SIFT"){//input should be the type, "SIFT" or "Normal Means"
        //     file << "Ship was balanced through SIFT" << endl;
        // }
        // else if(baltype == "NORMAL"){
        //     file << "Ship was balanced" << endl;
        // }
        file << ship <<" is balanced" << endl; //we probably done need to use input
    }
    else{printf("SYSTEM DOES NOT DETECT CURRENT LOG FILE...\n");}
    file.close(); //free file

}

void FinalUpdateLog(string n){ //takes output manifest
    printf("SYSTEM DETECTS THAT OPERATOR FINISHED WORKING ON SHIP\n");
    DateTime(); //get date and time
    ofstream file;
    file.open(path, ios_base::app); //open file in append mode
    if(file){
        file << date << ": " << time;
        file << " ";//Here should be 19 characters, we want lines of 
        file << "Finished a Cycle. Manifest ";
        file << n << " was written to desktop, and a reminder pop-up to operator to send file was displayed.\n";
    }
    else{printf("SYSTEM DOES NOT DETECT THE LOG FILE...\n");}
    file.close();
}

/*
    This next file with global variable is just a test case for the system. 
    Was attempting to see if the backup function would work correctly with this function.
    COMMENT OUT BEFORE DEPLOYMENT
*/
// int sTime = 0;
// void counter(){
//     ofstream file;
//     file.open(path, ios_base::app);  //Words in append mode 
//     if(file){
//         file << to_string(sTime) << endl; //send data to backup file
//         sTime++;
//     }
//     else{
//         cout <<"there is no file here..." << endl;
//     }
//     file.close(); //close file
// }

void BackupLogs(){ //backup system
    string backUp; //uses getline to copy data

    ifstream ogFile(path); //check for normal log file
    ofstream cpyFile(path_backup); //open output for backup file

    if(ogFile && cpyFile){ //check if both files are avaliable else system will not work
        while(getline(ogFile,backUp)){ //while there is still data in the system, back up
            cpyFile << backUp << "\n"; //send data inside 
        }
        printf("The file should be backed up!!! \n"); //console indication that file has been backed up
    }
    else{printf("One or both files do not exist \n");} //if one or both are not here, do nothing

    ogFile.close(); //close logfile
    cpyFile.close(); //close backupfile
    back = true; //limits backups

}

void StartLib(void){
    InitialStart();
    CreateFolder();
    CreateFile();
}
// ship balanced...when goal state print to log...
//need to create txt file that explains how to use the functions...
#endif