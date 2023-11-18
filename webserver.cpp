#include <iostream>
#include "dependencies/httplib.h"


/**
 * @fn Main section for application. Webserver will run from here
 * 
 * @todo Add other webserver endpoints for client to interact with server
*/
int main() {
    std::cout << "Starting server..." << std::endl;

    httplib::Server svr;

    /**
     * @fn Just for testing.
    */
    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    std::cout << "Listening on Port 8080" << std::endl;
    svr.listen("0.0.0.0", 8080);
}
