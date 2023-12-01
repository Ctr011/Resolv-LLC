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

    Currently debating whether this should turn into a class instead of an instruction file
*/
/*
    Declare Global Variables
*/
// class logging{ 
//     private:
//         const int max_char = 255;
//         string path, path_backup;
//         string filename, file_back;
//         string year;
//         string user;
//     bool back = false; //global var to stop system from wasting resources backing up for 1 minute

// };

const int max_char = 255;
const int max_line = 110;
string path, path_backup;
string filename, file_back;
string year;
string user;
// vector<string> users;
string craneop ="";
bool back = false; //global var to stop system from wasting resources backing up for 1 minute

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

void initialStart(){ //initial start.
    cout << "Getting %%USERPROFILE% " << endl; //initial statement
    user = GetUserProfile(); //call system info
    SYSTEMTIME st; //enter in system time
    filename = "log"; //original log file
    file_back = "log"; //backup log file
    path = "C:/Users/" + user+"/AppData/Roaming/ResolvDeckware/"; //current directory, user is obtained from GetUserProfile()
    path_backup = "C:/Users/" + user+"/AppData/Roaming/ResolvBack/"; //current backup directory, user is obtained from GetUserProfile()
    GetLocalTime(&st); //getting system time
    year = to_string(st.wYear); //setting the year
    filename += "_"+ year + ".txt"; //full file name
    file_back += "_" + year + "_backup.txt"; //full backup name
    path +=filename; //original file path
    path_backup += file_back; //backup file path
    createFolder();
    createFile();
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
void createFile(){
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
void createFolder(){ //test system
    string path_dir = "C:/Users/" + user +"/AppData/Roaming/"; //file system we can use
    string  path_folder = "ResolvDeckware"; //folder I want to hide
    string backup_folder = "ResolvBack"; //backup folder I want to hide
    string sys_path = path_dir + path_folder; //system path for directory
    string sys_back = path_dir + backup_folder; //backup path 

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
    if(n.size() == 1){ //if size of user input is 1, we check if its just a space...considered empty string
        if(n.at(i) == ' '){return true;}
    }
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
    SYSTEMTIME st;
    string month,day; //date
    string hour,minute; //time
    string date, time;
    GetLocalTime(&st);
    printf("INITIAL TEST FOR MANIFEST FILE...\n");
    cout << manifestName << endl;


    if(st.wMonth < 10){month = "0"; month += to_string(st.wMonth);}
    else {month = to_string(st.wMonth);}
    if(st.wDay < 10){day = "0"; day+= to_string(st.wDay);}
    else {day = to_string(st.wDay);}
    if(st.wHour < 10){hour = "0"; hour += to_string(st.wHour);}
    else {hour = to_string(st.wHour);}
    if(st.wMinute < 10){minute = "0"; minute += to_string(st.wMinute);}
    else{minute = to_string(st.wMinute);}
    date = month +"/"+day+"/"+year;
    time = hour +":" + minute;
    ofstream file;
    file.open(path , ios_base::app);
    if(file){

            printf("SYSTEM CANNOT DETECT PREVIOUS OP LOGIN...SIGNING IN NEW OP...\n");
            file << date << ": " << time;
            file << " ";//Here should be 19 characters, we want lines of 
            file << "Manifest " << manifestName << "is opened, there are " << "CHANGE SOON" <<" containers on the ship";
            file << "\n";
     }
     else{printf("SYSTEM IS NOT DETECTING THE LOG FILE CURRENTLY...\n");}

    return;
}
void UpdateFileLogin(string userlogging){ //deisgned for user login
    SYSTEMTIME st;
    string month,day; //date
    string hour,minute; //time
    string date, time;
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
    time = hour +":" + minute;

    ofstream file;
    file.open(path , ios_base::app);
    if(file){
        if(craneop == ""){//System Restarted, now there is no crane op logged in
            printf("SYSTEM CANNOT DETECT PREVIOUS OP LOGIN...SIGNING IN NEW OP...\n");
            file << date << ": " << time;
            file << " ";//Here should be 19 characters, we want lines of 
            file << userlogging << " signs in" << "\n";

        }
        else if(craneop != userlogging){
            printf("SYSTEM DETECTED NEW OPERATOR LOGIN...SIGNING OUT PREVIOUS OP...\n");
            file << date << ": " << time;
            file << " ";//Here should be 19 characters, we want lines of 
            file << craneop << " signs out" << "\n";
            file << date << ": " << time;
            file << " ";//Here should be 19 characters, we want lines of 
            file << userlogging << " signs in" << "\n";


     }
     craneop = userlogging;
    }
    else{printf("SYSTEM IS NOT DETECTING THE LOG FILE CURRENTLY...\n");}
    file.close();
    return;
}

void WritingSystem(string n){ //for parsing user input to file
    vector<string> containerCheck;
    string input="";
    SYSTEMTIME st;
    /*
        Setting up needed vars
    */
    string month,day; //date
    string hour,minute; //time
    string date, time;
    int spaces=0;
    printf("SYSTEM HAS DETECTED USER INPUT...\n");

    if(UserLimit(n) == true){ //check if user input exceeds max character limit
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
            spaces++; //put in all current words into vectors
        }
    }

    if(CheckRestrictedChars(n) == true ) {//checking for Restricted Characters
        printf("System Detected Restricted Character...Forcing EXIT... \n"); //backend error
        return;} //error out
    if(CheckRestrictedWords(containerCheck) == true) { //checking for restricted words
        printf("System Detected Restricted Words...Forcing Exit... \n");
        return;} //error out

    /*
        Setting all variables with their data. Since most will be pushed to txt file, we
        need to create strings out of all time variables. Additional help needed to add "0"
        to comply with MM/DD/YYYY format
    */
    GetLocalTime(&st); //getting current information...
    if(st.wMonth < 10){month = "0"; month += to_string(st.wMonth);}
    else {month = to_string(st.wMonth);}
    if(st.wDay < 10){day = "0"; day+= to_string(st.wDay);}
    else {day = to_string(st.wDay);}
    if(st.wHour < 10){hour = "0"; hour += to_string(st.wHour);}
    else {hour = to_string(st.wHour);}
    if(st.wMinute < 10){minute = "0"; minute += to_string(st.wMinute);}
    else{minute = to_string(st.wMinute);}
    date = month +"/"+day+"/"+year;
    time = hour +":" + minute;

    ofstream file;
    file.open(path, ios_base::app); //File opens in append mode
    if(file){
        int cnt = 19;
        file << date << ": " << time;
        file << " ";//Here should be 19 characters, we want lines of 
        int i = 0;
        while(containerCheck.size() > i){
            cnt += containerCheck.at(i).size()+1;
            if(cnt <= max_line){
                file << containerCheck.at(i);
                file << " ";
            }
            else{
                file << "\n" << containerCheck.at(i); 
                file << " ";
                cnt = containerCheck.at(i).size()+1; 
            }
            i++;
        }
        file << '\n';
    }
    else{printf("SYSTEM ERROR...FILE DOES NOT EXIST...\n");} //backend error
    file.close();
    return;
} 

/*
    This next file with global variable is just a test case for the system. 
    Was attempting to see if the backup function would work correctly with this function.
    COMMENT OUT BEFORE DEPLOYMENT
*/
int sTime = 0;
void counter(){
    ofstream file;
    file.open(path, ios_base::app);  //Words in append mode 
    if(file){
        file << to_string(sTime) << endl; //send data to backup file
        sTime++;
    }
    else{
        cout <<"there is no file here..." << endl;
    }
    file.close(); //close file
}

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


// ship balanced...when goal state print to log...