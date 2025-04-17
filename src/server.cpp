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
            res.status = 400;
            res.set_content("Missing device_id parameter", "text/plain");
            return;
        }

        try {
            json payload = json::parse(req.body);
            if(payload.contains("content") && payload.contains("content_type"))
            {
                std::lock_guard<std::mutex> lock(clipboard_mutex);
                clipboard_data[device_id] = payload;
                res.status = 200;
            }
            else 
            {
                res.status = 400;
                res.set_content("Invalid JSON payload", "text/plain");
            }
        }catch(const json::parse_error& e){
            res.status = 400;
            res.set_content("Invalid JSON format", "text/plain");
        }
    });

    //获取最新剪切板内容(来自其他设备)
    serv.Get("/clipboard", [&](const Request& req, Response& res){
        std::string current_device_id = req.get_param_value("device_id");
        if(current_device_id.empty())
        {
            res.status = 400;
            res.set_content("Missing device_id parameter", "text/plain");
            return;
        }

        json latest_content;
        std::lock_guard<std::mutex> lock(clipboard_mutex);
        for (const auto& pair : clipboard_data)
        { 
            std::cout << pair.first << ", " << pair.second << std::endl;
            if(pair.first != current_device_id)
            {
                latest_content = pair.second;
                break;
            }
        }
        
        res.set_header("Content-Type", "application/json");
        res.set_content(latest_content.dump(), "application/json");
    });
   
    std::cout << "Clipboard server listening on port 8080..." << std::endl;
    serv.listen("0.0.0.0", 8080);

    return 0;
}