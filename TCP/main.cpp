#include <print>
#include "src/Server.h"
#include "src/Request/Request.h"
#include "src/Response/Response.h"

int main() {
    Server server{ "0.0.0.0" , 6788 };

    server.Get("/redirect", [](const auto& req, const auto& res) -> void {
        // Example
        // res.setStatus(404);
        // res.setResponse("example response");
        // res.redirect(mainpage);
    });

    int err { server.run() };
    if (err == 1) {
        std::println("Error!");
    }

    return 0;
}