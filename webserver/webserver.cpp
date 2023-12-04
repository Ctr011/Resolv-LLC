#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>

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
#include "./httplib.h"
using namespace std;

int main() {

    //  Init sever and active ShipBay
    httplib::Server svr;

    // Serve static files from the "webpage" directory
    svr.set_mount_point("/", "../webpage");

    // Serve other static files (JS, CSS, etc.)
    svr.set_mount_point("/JS", "../webpage/JS");
    svr.set_mount_point("/CSS", "../webpage/CSS");

    // Serve HTML file
    svr.Get("/", [](const httplib::Request &, httplib::Response &res) {
        std::ifstream file("../webpage/HTML/fileupload.html");
        std::stringstream buffer;
        buffer << file.rdbuf();
        res.set_content(buffer.str(), "text/html");
    });

    // Just for testing
    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    // Endpoint to accept file uploads from the frontend
    svr.Post("/upload", [&](const httplib::Request &req, httplib::Response &res) {
        if (req.has_file("file")) {
            const auto &file = req.get_file_value("file");
            std::istringstream filestream(file.content);

            // Print the content line by line
            string curr_line;
            int entries = 0;
            std::vector<std::string> data;
            while (getline(filestream, curr_line)) {
                std::cout << "Line " << entries + 1 << ": " << curr_line << std::endl;
                data.push_back(curr_line);
                entries++;
            }
            ShipBay* bay = nullptr;
            ShipBay* bay2 = nullptr;
            Buffer* buffer = nullptr;
            Buffer* buffer2 = nullptr;

            try{
                bay = new ShipBay(file.content);

                // bay2 = new ShipBay(file.content);

                buffer = new Buffer("");
                // buffer2 = new Buffer("");

                //  init initial node
                Node* testNode = new Node(bay, buffer, 0);

                Tree* tree = new Tree(testNode, new UnloadQueue());

                // if(bay->canBalance()){
                //     tree = new Tree(testNode, new BalanceQueue());
                //     tree->solveBalance();
                // }else{
                //     tree = new Tree(testNode, new SIFTQueue());
                //     tree->solveSIFT(siftTest);
                // }
                testNode->setUnloadTarget("Cat");
                tree->solveUnLoad("Cat", testNode);
                


            }catch(std::invalid_argument error){
                res.status = 500;
                res.set_content("Manifest Parsing Error", "text/plain");
                return;
            }


            bay->getHeights(1, 12);

            // Status code 200: Success
            res.status = 200;
            res.set_content("File successfully uploaded", "text/plain");
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
    svr.listen("localhost", 8080);

    return 0;
}