#include <print>
#include "src/Server.h"
#include "src/Request/Request.h"
#include "src/Response/Response.h"

int main() {
    Server server{ "0.0.0.0" , 6788 };

    server.Get("/redirect", [](Request& req, Response& res) -> void {
        res.setStatus(200);
        res.sendPage("../html/test.html");
    });

    // server.Post("/redirect", [](Request& req, Response& res) -> void {
    //     // Example
    //     res.setStatus(200);
    //     res.sendPage("../html/test.html");
    // });




    int err { server.run() };
    if (err == 1) {
        std::println("Error to Start The Server!");
    }

    return 0;
}