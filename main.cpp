#include <iostream>
#include <curl/curl.h>
#include <string>
#include <cstring>
using namespace std;

size_t write_data(char *ptr, size_t size, size_t nmemb, std::string *data)
{
    if (data)
    {
        data->append(ptr, size * nmemb);
        return size * nmemb;
    }
    else
        return 0; //error
}

int main(int argc, char *argv[])
{
    //cout << curl_version() << endl;
    //======================================

    string method_name = "systemInfo";
    // string params = "[]";

    if (argc >= 2)
    {
        method_name = argv[1];
    }
    // cout << "Method name: " << method_name << endl;

    // if (argc >= 3)
    // {
    //     params = "[";
    //     for (int i = 2; i < argc; i++){
    //         params += argv[i];
    //     }
    //     params += "]";
    // }
    // cout << "Params: " << params << endl;

    //======================================
    //For tests:
    //const char *address = "https://httpbin.org/post";
    const char *address = "http://localhost:8000/api/json/v2";
    std::string result_req = "";
    const char *dataFormat = "{\"jsonrpc\": \"2.0\", \"id\":\"0\", \"method\": \"%s\", \"params\": [] }";

    CURL *curl;
    curl = curl_easy_init();

    if (curl)
    {
        struct curl_slist *headers = NULL;
        headers = curl_slist_append(headers,"content-type: application/json;");//"Content-Type application/json");
        curl_easy_setopt(curl, CURLOPT_HTTPHEADER, headers);

        curl_easy_setopt(curl, CURLOPT_URL, address);
        curl_easy_setopt(curl, CURLOPT_FOLLOWLOCATION, 50L);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &result_req);

        //req
        char *req = new char[strlen(dataFormat) + method_name.length() + 1];
        sprintf(req, dataFormat, method_name.c_str());
        // cout << "Req: " << req << endl;
        curl_easy_setopt(curl, CURLOPT_POSTFIELDSIZE, (long)strlen(req));
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, req);

        CURLcode res = curl_easy_perform(curl);
        if (res)
        {
            std::cout << "res curl error: " << res << std::endl;
        }
        else
        {
            cout << result_req << endl;
        }
        curl_easy_cleanup(curl);
    }
    curl_global_cleanup();
    return 0;
}