#include <string>
#include <map>
#include <functional>
#include <iostream>
#include "Response.h"
#include "../Request/Request.h"

bool Response::findRoute(const std::string& path, const std::map<std::string, std::function<void(const Request&, const Response&)>>& routes) const {
    auto it { routes.find(path) };

    if (it != routes.end()) {
        std::cout << "Found Route!\n";
        return true;
    }

    std::cout << "Didn't found any Route!\n";
    return false;
}