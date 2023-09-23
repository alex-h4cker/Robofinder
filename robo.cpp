#include <iostream>
#include <string>
#include <curl/curl.h>
#include <jsoncpp/json/json.h>

using namespace std;

class URL {
     
    public:
    
    string address;
    string robo;
    string add;
};

void clear_screen() {
    system("clear"); 
}

size_t WriteCallback(void* contents, size_t size, size_t nmemb, string* response)
{
    size_t totalSize = size * nmemb;
    response->append((char*)contents, totalSize);
    return totalSize;
}

int main() {

    clear_screen();
   
    cout << " ======================================= " << endl;
    cout << "|                                       |" << endl;
    cout << "|             RoboFinder                |" << endl;
    cout << "|                                       |" << endl;
    cout << " ======================================= " << endl;

    URL u1;

    start:
    cout << "Enter URL: ";
    cin >> u1.address;

    u1.robo = "/robots.txt";
    u1.add = u1.address + u1.robo;
   
    CURL* curl = curl_easy_init();
    if (curl) {
        
        curl_easy_setopt(curl, CURLOPT_URL, u1.add.c_str());

        
        string response;
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);

        
        CURLcode res = curl_easy_perform(curl);
        
        
        if (res != CURLE_OK) {
            cerr << "cURL request failed: " << curl_easy_strerror(res) << endl;
            return 1;
        }

        
        curl_easy_cleanup(curl);

        
        Json::CharReaderBuilder readerBuilder;
        
        Json::Value jsonData;
        
        istringstream jsonStream(response);
        
        if (!Json::parseFromStream(readerBuilder, jsonStream, &jsonData, nullptr)) {
        
        cerr << "Failed to parse JSON data" << endl;
        
        return 1;
        
        }
        
        cout << jsonData.toStyledString() << endl;

       } else {
       
       cerr << "Failed to initialize cURL" << endl;
       
       return 1;
       }

      char select;
         
      cout << "Do you want to continue(y | n): ";
      
      cin >> select;

      if (select == 'y') {
      
        goto start;
        
      }
      else if (select == 'n') {
      
        return 0;
     }
}
