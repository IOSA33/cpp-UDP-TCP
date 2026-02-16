#include <print>
#include "src/Server.h"
#include "src/Request/Request.h"
#include "src/Response/Response.h"

int main() {
    Server server{ "0.0.0.0" , 6788 };

    server.Use("PageNotFound", [](Request& req, Response& res) -> void {
        res.setStatus(301);
        res.redirect("https://www.youtube.com");
    });

    server.Get("/htmltest", [](Request& req, Response& res) -> void {
        res.setStatus(200);

        std::println("Host is: {}", req.getHeader("Host"));
        // res.setHeader(key, value);
        res.sendFile("../html/test.html");
    });

    server.Post("/htmltest", [](Request& req, Response& res) -> void {
        res.setStatus(200);
        res.sendFile("../html/htmlPostTest.html");
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