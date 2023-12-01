#include <iostream>
#include <fstream>
#include <Windows.h>
#include <cstdlib>
#include <vector>
#include <filesystem>
#include <stdio.h>
#include <string>
#include "./logcreate.cpp"


using namespace std;


int main(){ //test units...system testing 
    //GetUserProfile();
    cout << "Initialize Global Vars..." << endl;
    initialStart();
    cout << "Testing Folder Creation" << endl;
    createFolder();
    cout << "Testing File Creation" << endl;
    createFile();
    cout << "Testing Backup Solution" << endl;
    BackupLogs();

    
    cout << "test timing for backups" << endl;
    // while(1){    //this loop will probably be the server which will continuously run, allowing us to add some sort of back up system
    //     //writingSystem();
    //     counter(); //test function for backup, just loads numbers to the log file. NOT FOR DEPLOYMENT
    //     if((getTime() == 00 || getTime() == 30) && back == false ){ //this system inside the loop (webserver)
    //         BackupLogs();
    //     }
    //     if(getTime() != 00 && getTime() != 30){ //resets the flag for backup server
    //         back=false;
    //     }

    //     //BREAK LOOP THROUGH CTRL+C COMBINATION
    // }
    
    cout << "Testing Writing System" << endl;
    string test1 = "Today's container was throughly inspected and charged.";
    string test2 = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. ";
    test2+="Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, ";
    test2+="nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis,.";
    string test3 = "abc def ghi jkl mno pqrs tuv wxyz ABC DEF GHI JKL MNO PQRS TUV WXYZ !";
    test3 +="\"§ $%& /() =?* '<> #|; ²³~ @`´ ©«» ¤¼× {} abc def ghi jkl mno pqrs tuv wxyz ABC DEF GHI JKL MNO PQRS TUV WXYZ !";
    test3 += "§ $%& /() =?* '<> #|; ²³~ @`´ ©«» ¤¼× {} abc def ghi jkl mno pqrs tuv wxyz ";
    string test4 = "Lorem ipsum dolor sit amet, consectetuer adipiscing elit. ";
    test4+="Aenean commodo ligula eget dolor. Aenean massa. Cum sociis natoque penatibus et magnis dis parturient montes, ";
    test4+="nascetur ridiculus mus. Donec quam felis, ultricies nec, pellentesque eu, pretium quis,";
    WritingSystem(test1); //Normal Limit String Test
    WritingSystem(test4); //Max Character Test
    WritingSystem(test2); //Exceed Max Character Test
    WritingSystem(test3); //Random Variable Test

    printf("SYSTEM IS TESTING USER LOGINS\n");
    printf("TEST1\n");
    UpdateFileLogin("James Anderson");
    printf("TEST2\n");
    UpdateFileLogin("Sandy Hills");
    printf("TEST3\n");
    UpdateFileLogin("Ren Sumzki");

    return 0;
}