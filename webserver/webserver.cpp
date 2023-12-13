#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#define NOMINMAX
#include <WinSock2.h>
#include <windows.h>
//#include <MyClass.h>

#include "../ContainerSlot.h"
#include "../ContainerSlot.cpp"
#include "../ShipBay.h"
#include "../ShipBay.cpp"
#include "../Buffer.h"
#include "../Buffer.cpp"
#include "../Node.h"
#include "../Node.cpp"
#include "../NodeQueue.h"
#include "../NodeQueue.cpp"
#include "../Tree.h"
#include "../Tree.cpp"
#include "../NodeQueue.h"
#include "../NodeQueue.cpp"
#include "./httplib.h"
#include "../logcreate.h"
#include "../logcreate.cpp"

using namespace std;

//  Doesnt rteally do Anything, just holds code here
void solveLoad(){
    // bay = new ShipBay(file.content);
    //             buffer = new Buffer("");

    //             Container* batteries = new Container("BAT1", 431, 1, 1, Origin::TRUCK);
    //             Container* batteries2 = new Container("BAT2", 431, 1, 1, Origin::TRUCK);

    //             std::vector<Container*> containers;
    //             containers.push_back(batteries);
    //             containers.push_back(batteries2);


    //             //  Get initial start state
    //             solution_response["startState"] = bay->getText();

    //             int movenumber = 0;
    //             for(Container* c : containers){
    //                 movenumber++;
    //                 Node* testNode = new LoadNode(bay, buffer, 0, batteries);
    //                 Tree* tree = new Tree(testNode);

    //                 solution_response[std::to_string(movenumber)] = tree->solveLoad();

    //                 delete bay;
    //                 bay = new ShipBay(solution_response[std::to_string(movenumber)]["endState"]);

    //                 solution_response["endState"] = solution_response[std::to_string(movenumber)]["endState"];
    //                 solution_response[std::to_string(movenumber)].erase("endState");

    //                 delete testNode;
    //                 delete tree;
    //             }


                
                

    //             std::cout << "JSON Object:\n" << solution_response.dump(2) << std::endl;
}

int main() {

    //  Init sever and active ShipBay
    httplib::Server svr;
    StartLib();
    string myData;
    string username;
    string usernotes;
    bool bal, off;

    ShipBay* bay = nullptr;
    ShipBay* bay2 = nullptr;
    Buffer* buffer = nullptr;
    Buffer* buffer2 = nullptr;
    Node* testNode;
    Json solution_response;
    string weight, conname;
    vector<vector<string>> contload;
    vector<vector<string>> contoff;
    // Serve static files from the "webpage" directory
    svr.set_mount_point("/", "../webpage");
    svr.set_base_dir("../webpage/HTML");

    // Serve other static files (JS, CSS, etc.)
    svr.set_mount_point("/JS", "../webpage/JS");
    svr.set_mount_point("/CSS", "../webpage/CSS");
    svr.set_mount_point("HTML", "../webpage/HTML");

    // Serve HTML file
    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        std::ifstream file("../webpage/HTML/intro.html");
        std::stringstream buffer;
        buffer << file.rdbuf();
        res.set_content(buffer.str(), "text/html");
    });

    // svr.Get("/balance", [](const httplib::Request &, httplib::Response &res) {

    //     res.set_content();

    // });
    // Just for testing
    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) { 
        res.set_content("Hello World!", "text/plain");
    });
    
    svr.Post("/start", [](const httplib::Request & req, httplib::Response &res){//function starts either balance or offload
        if(req.has_file("bth")){
            cout <<"Starting Function..." << endl;
            res.status = 200;
            res.set_content("Program Starting...", "text/plain");
            return;
        }
        else{
            res.status = 400;
            res.set_content("USER NOT FOUND: ", "text/plain");
            return;
        }
    });
    svr.Post("/id", [](const httplib::Request & req, httplib::Response &res){//header values
        if(req.has_file("name")){
            const auto &username = req.get_file_value("name");
            res.status = 200;
            res.set_content("USERID FOUND: ", "text/plain");
            std::cout << "ID: " << username.content << std::endl;
            UpdateFileLogin(username.content);   
            return;
        }
        else{
            res.status = 400;
            res.set_content("USER NOT FOUND: ", "text/plain");
            return;
        }
    });

    
    svr.Post("/notes", [](const httplib::Request & req, httplib::Response &res){//header values
        if(req.has_file("nnote")){
            const auto &usernotes = req.get_file_value("nnote");
            res.status = 200;
            res.set_content("USERID FOUND: ", "text/plain");
            std::cout << "Custom Note: " << usernotes.content << std::endl;
            WritingSystem(usernotes.content);   
            return;
        }
        else{
            res.status = 400;
            res.set_content("USER NOT FOUND: ", "text/plain");
            return;
        }
    });
    
    svr.Post("/contname", [](const httplib::Request & req, httplib::Response &res){//header values
        if(req.has_file("contn")){
            if(req.has_file("contw")){
                const auto& conname = req.get_file_value("contn");
                const auto& weight = req.get_file_value("contw");
                cout << "Container Name: " << conname.content << endl;
                cout << "Container Weight: " << weight.content << endl;
                res.status = 200;
                res.set_content("Container Found...", "text/plain");
            return;}
            else{
            res.status = 400;
            res.set_content("Weight Not Found...", "text/plain");
            return;
            }
        }
        else{
            res.status = 400;
            res.set_content("Container Name Not Found...", "text/plain");
            return;
        }
    });

    // Endpoint to accept file uploads from the frontend
    svr.Post("/balanced", [&](const httplib::Request &req, httplib::Response &res) {
        if (req.has_file("bala")) {

            const auto &file = req.get_file_value("bala");
            const auto &myData = req.get_file_value("id");
            std::istringstream filestream(file.content);
            bal = true;
            off = false;
            

            // Print the content line by line
            string curr_line;
            int entries = 0;
            std::vector<std::string> data;
            while (getline(filestream, curr_line)) {
                std::cout << "Line " << entries + 1 << ": " << curr_line << std::endl;
                data.push_back(curr_line);
                entries++;
            }

            try{
                bay = new ShipBay(file.content);
                
                buffer = new Buffer("");

                testNode = new BalanceNode(bay, buffer, 0);
                

                Tree* tree = new Tree(testNode);

                

                if(bay->canBalance()){
                    solution_response = tree->solveBalance();
                }else{
                    testNode->isSIFT = true;
                    solution_response = tree->solveSIFT(bay->getSIFTState());
                }

            }catch(std::invalid_argument error){
                res.status = 500;
                res.set_content("Manifest Parsing Error", "text/plain");
                return;
            }


            bay->getHeights(1, 12);

            // Status code 200: Success
            res.status = 200;
            res.set_content(solution_response.dump(), "application/json");
            UpdateFileM(file.filename);
            return;
        } else {
            // HTTP status code set to 400: Bad Request
            res.status = 400;
            res.set_content("No file uploaded", "text/plain");
            return;
        }
        
    });

    svr.Post("/load", [&](const httplib::Request &req, httplib::Response &res) {
        if (req.has_file("offload")) {

            const auto &file = req.get_file_value("offload");
            const auto &myData = req.get_file_value("id");
            std::istringstream filestream(file.content);
            bal = false;
            off = true;

            // Print the content line by line
            string curr_line;
            int entries = 0;
            std::vector<std::string> data;
            while (getline(filestream, curr_line)) {
                std::cout << "Line " << entries + 1 << ": " << curr_line << std::endl;
                data.push_back(curr_line);
                entries++;
            }

            try{
                bay = new ShipBay(file.content);
                buffer = new Buffer("");

                testNode = new BalanceNode(bay, buffer, 0);
                

                Tree* tree = new Tree(testNode);

                

                if(bay->canBalance()){
                    solution_response = tree->solveBalance();
                }else{
                    testNode->isSIFT = true;
                    solution_response = tree->solveSIFT(bay->getSIFTState());
                }

            }catch(std::invalid_argument error){
                res.status = 500;
                res.set_content("Manifest Parsing Error", "text/plain");
                return;
            }


            bay->getHeights(1, 12);

            // Status code 200: Success
            res.status = 200;
            res.set_content(solution_response.dump(), "application/json");
            UpdateFileM(file.filename);
            return;
        } else {
            // HTTP status code set to 400: Bad Request
            res.status = 400;
            res.set_content("No file uploaded", "text/plain");
            return;
        }
        
    });




    // Run web server on localhost (127.0.0.1)
    std::cout << "Deckware Web Server listening on Port 8080..." << std::endl;
    // std::cout << "here is path: ";
    // std::cout << path << endl;
    svr.listen("localhost", 8080);
    //to run through dev cmd, used code .
    return 0;
}