#include <fstream> // for file input
#include "dependencies/httplib.h"
#include "classes/ContainerSlot.h"


/**
 * @fn Main section for application. Webserver will run from here
 * 
 * @todo Add other webserver endpoints for client to interact with server
*/
int main() {

    Container c("testContainer", 99.99, 0, 0);
    c.toString();

    //  Init webserver here
    httplib::Server svr;

    /**
     * @fn Just for testing.
    */
    svr.Get("/hi", [](const httplib::Request &, httplib::Response &res) {
        res.set_content("Hello World!", "text/plain");
    });

    std::cout << "Deckware Web Server listening on Port 8080..." << std::endl;
    svr.listen("0.0.0.0", 8080);
}
