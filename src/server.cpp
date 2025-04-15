#include "httplib.h"

#include <iostream>
#include <vector>
#include <mutex>
#include <algorithm>
#include <map>
#include <nlohmann/json.hpp>

using namespace httplib;
using json = nlohmann::json;

std::map<std::string, json> clipboard_data;
std::mutex clipboard_mutex;

int main()
{
    // HTTP
    Server serv;
    
    //接收并存储剪切板
    serv.Post("/clipboard", [&](const Request& req, Response& res){
        std::string device_id = req.get_param_value("device_id");
        if(device_id.empty())
        {
            res.set_header("status", "500");
            res.set_content("Missing device_id parameter", "text/plain");
            return;
        }
    });

    std::cout << "Clipboard server listening on port 8080..." << std::endl;
    serv.listen("0.0.0.0", 8080);

    return 0;
}