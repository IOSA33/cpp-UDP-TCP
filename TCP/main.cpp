#include <print>
#include "src/Server.h"
#include "src/Request/Request.h"
#include "src/Response/Response.h"

int main() {
    Server server{ "0.0.0.0" , 6788 };

    server.Get("/htmltest", [](Request& req, Response& res) -> void {
        res.setStatus(200);
        // res.setHeader(key, value);
        res.sendFile("../html/test.html");
    });

    server.Post("/htmltest", [](Request& req, Response& res) -> void {
        res.setStatus(200);
        res.sendFile("../html/test.json");
    });
    
    server.Get("/jsontest", [](Request& req, Response& res) -> void {
        res.setStatus(200);
        res.sendFile("../html/test.json");
    });

    int err { server.run() };
    if (err == 1) {
        std::println("Error to Start The Server!");
    }

    return 0;
}