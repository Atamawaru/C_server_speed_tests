
#include <curl/curl.h>
#include <cjson/cJSON.h>

#include <stdio.h>
int main(int argc, char *argv[]){
    CURL *curl;
    curl = curl_easy_init();
    printf("Hello world!\n");
    curl_easy_cleanup(curl);
    return 0;
}
