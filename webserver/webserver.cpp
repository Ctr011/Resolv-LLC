#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#define NOMINMAX
#include <WinSock2.h>
#include <windows.h>
#include <filesystem>
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
#include "../cmd.cpp"

using namespace std;

string trim(string str) {
    size_t start = str.find_first_not_of(" \t\n\r");
    size_t end = str.find_last_not_of(" \t\n\r");

    if (start == string::npos || end == string::npos) {
        // The string is empty or contains only whitespaces
        return "";
    }

    return str.substr(start, end - start + 1);
}

int main() {

    //  Init sever and active ShipBay
    httplib::Server svr;
    StartLib();
    string myData;
    string username;
    string usernotes;
    bool bal, off;

    ShipBay* bay;
    ShipBay* bay2;
    Buffer* buffer;
    Buffer* buffer2;
    Node* testNode;
    Json solution_response;
    string weight, conname;
    std::string filecon = "";
    Json startData;

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

    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) { 
        res.set_content("Hello World!", "text/plain");
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

    svr.Post("/done", [](const httplib::Request & req, httplib::Response &res){
        if(req.has_file("finished")){
            //need to add the final output for the new manifest
            //add data for the manifest
            string path_to_out = desloc + newMan + "OUTBOUND.txt";
            ifstream file;
            file.open(path_to_out);
            if(file){}
            else{printf("ERROR!!\n");}
            file.close();

            ofstream file_out;
            file_out.open(path_to_out);


            res.status = 200;
            return;
        }
        else{
            res.status = 400;
            res.set_content("System Cannot Complete Task...", "text/plain");
            return;
        }
    });
    
    svr.Post("/cont/load", [](const httplib::Request & req, httplib::Response &res){//header values
        if(req.has_file("contn")){
            if(req.has_file("contw")){
                const auto& conname = req.get_file_value("contn");
                const auto& weight = req.get_file_value("contw");
                cout << "Container Name: " << conname.content << endl;
                cout << "Container Weight: " << weight.content << endl;
                if(!CheckRestrictedChars(conname.content) && !CheckRestrictedChars(weight.content)){
                get_loads(conname.content,stoi(weight.content));
                cout << "Container Name: " << load[0].first << endl;
                cout << "Container Weight: " << load[0].second << endl;}
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

     svr.Post("/cont/unload", [](const httplib::Request & req, httplib::Response &res){//header values
        string confirm;
        if(req.has_file("contn")){
            if(req.has_file("contw")){
                const auto& conname = req.get_file_value("contn");
                const auto& weight = req.get_file_value("contw");
                const auto& confirm = req.get_file_value("delete_data");
                if(confirm.content != "Yes"){
                cout << "Container Name: " << conname.content << endl;
                cout << "Container Weight: " << weight.content << endl;
                get_unloads(conname.content,stoi(weight.content));
                cout << "Container Name: " << unload[0].first << endl;
                cout << "Container Weight: " << unload[0].second << endl;
                }
                else if(confirm.content == "Yes"){
                    delete_unloads(conname.content,stoi(weight.content));
                }
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

            //  Assign file content to global filecon variable
            std::string curr_line;
            int entries = 0;
            filecon = "";
            while (getline(filestream, curr_line)) {
                std::cout << "Line " << entries + 1 << ": " << curr_line << std::endl;
                filecon += curr_line + "\n";
                entries++;
            }

            if(entries != 96){
                res.status = 400;
                res.set_content("Bad file format", "text/plain");
                return;
            }

            bal = false;
            off = true;
            // Print the content line by line
            std::vector<std::string> data;
            while (getline(filestream, curr_line)) {
                std::cout << "Line " << entries + 1 << ": " << curr_line << std::endl;
                data.push_back(curr_line);
                entries++;
            }

            try{
                bay = new ShipBay(file.content);
                buffer = new Buffer("");

                // testNode = new BalanceNode(bay, buffer, 0);
                

                // Tree* tree = new Tree(testNode);


                string start_json = bay->getText();
                startData["startState"] = start_json;
                startData.dump(2);
              
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

    svr.Post("/start/load", [&](const httplib::Request & req, httplib::Response &res){//function starts either balance or offload
        if(req.has_file("start")){
            Node* first[100];
            Node* tess[100];
            Json finishCode;
            bay = new ShipBay(filecon);

            //  To store total cost
            int total_cost = 0;

            //  Keep track of themove number
            int movenumber = 0;

            // buffer = new Buffer("");
            cout <<"Starting Function..." << endl;
            if(unload.size() > 0){
                cout << "Unload Request Size: " << std::to_string(unload.size()) << endl;
                vector<Container*> unloadContainers;

                //  Load all of the containers
                for(int i = 0; i < unload.size(); i++){
                    unloadContainers.push_back(new Container(unload[i].first, unload[i].second, 1,1,Origin::TRUCK));
                }

                //  Add state state data
                solution_response["startState"] = bay->getText();

                int i = 0;
                for(Container* container : unloadContainers){

                    //  Keep track of moveNumber
                    movenumber++;
                    std::string moveNumString = std::to_string(movenumber);
                    

                    Node* testNode = new UnloadNode(bay, buffer, 0, container->getName());
                    Tree* tree = new Tree(testNode);

                    solution_response[moveNumString] = tree->solveUnLoad(container->getName());
                    solution_response[moveNumString]["movetype"] = "UNLOAD"; //  Set movetype here

                    bay = new ShipBay(solution_response[moveNumString]["endState"]);

                    solution_response["endState"] = solution_response[moveNumString]["endState"];
                    solution_response[moveNumString].erase("endState");

                    std::cout << "JSON Object:\n" << solution_response.dump(2) << std::endl;

                    std::string costString = solution_response[moveNumString]["cost"];
                    total_cost += std::stoi(costString);

                    //  Needed to avoid memory leakage
                    delete testNode;
                    delete tree;

                    i++;
                }
            }
            if(load.size() > 0){
                cout << "Load Request Size: " << load.size() << endl;
                vector<Container*> container;

                for(int i = 0; i < load.size(); i++){
                    container.push_back(new Container(load[i].first, load[i].second, 1,1,Origin::TRUCK));
                }
                
                //  If there are no unloads, our start state is not init yet either .
                //  Do so here
                if(solution_response.find("startState") == solution_response.end()){
                    solution_response["startState"] = bay->getText();
                }

                
                int i = 0;
                for(Container* c : container){

                    movenumber++;
                    Node* testNode = new LoadNode(bay, buffer, 0, c);
                    Tree* tree = new Tree(testNode);

                    solution_response[std::to_string(movenumber)] = tree->solveLoad();
                    solution_response[std::to_string(movenumber)]["movetype"] = "LOAD"; //  Set movetype here

                    // delete bay;
                    bay = new ShipBay(solution_response[std::to_string(movenumber)]["endState"]);

                    solution_response["endState"] = solution_response[std::to_string(movenumber)]["endState"];
                    solution_response[std::to_string(movenumber)].erase("endState");


                    std::string costString = solution_response[std::to_string(movenumber)]["cost"];
                    total_cost += std::stoi(costString);
                    
                    //  Needed to avoid memory leakage
                    delete testNode;
                    delete tree;

                    i++;
                }

                //  Add total cost
                solution_response["totalCost"] = std::to_string(total_cost);
                std::cout << "JSON Solution:\n" << solution_response.dump(2) << std::endl;
                


                for (Container* c : container) {
                    delete c;
                }
                delete bay;


            }
            res.status = 200;
            res.set_content(solution_response.dump(), "application/json");
            return;
        }
        else{
            res.status = 400;
            res.set_content("USER NOT FOUND: ", "text/plain");
            return;
        }
    });

    /**
     * @fn /clear/load
     * Clears load and unload vectors 
    */
    svr.Get("/clear/load", [&](const httplib::Request & req, httplib::Response &res){
        clear_load();
        clear_unload();
    });



    // Run web server on localhost (127.0.0.1)
    std::cout << "Deckware Web Server listening on Port 8080..." << std::endl;
    // std::cout << "here is path: ";
    // std::cout << path << endl;
    svr.listen("localhost", 8080);
    //to run through dev cmd, used code .
    return 0;
}