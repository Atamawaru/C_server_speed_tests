
#include <curl/curl.h>
#include <cjson/cJSON.h>
#include <getopt.h>
#include <bits/getopt_core.h>

#include <curl/easy.h>
#include <curl/system.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define IP_GEO_API "http://ip-api.com/json/"

typedef struct{
    char *string;
    size_t size;
}Response;

size_t dummy_write(void *buffer, size_t size, size_t nmemb, void *userp);

size_t write_chunk(void *buffer, size_t size, size_t nmemb, void *userp);

void print_help();

Response get_geo_response(CURL *curl, Response *response);

int main(int argc, char *argv[]){
    
    char *file_buffer;
    long file_length;

    FILE *file = fopen("example_speedtest_server_list.json", "rb");

    if (file) {
        fseek(file, 0, SEEK_END);
        file_length = ftell(file);
        fseek(file, 0, SEEK_SET);
        file_buffer = malloc(file_length * sizeof(char*) + 1);
        if (file_buffer) {
            fread(file_buffer, 1, file_length, file);
        }
        file_buffer[file_length] = '\0';
        fclose(file);
    }
    else {
        perror("Error opening file");
        return -1;
    }
    cJSON *root = cJSON_Parse(file_buffer);
    cJSON *server;
    if (root == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error parsing JSON file: %s\n", error_ptr);
        }
        return -2;
    }
    free(file_buffer);
    int num_of_objects = cJSON_GetArraySize(root);

    int opt;
    char* only_upload_host = "";
    char* only_download_host = "";
    bool only_upload = false;
    bool only_download = false;
    bool get_best_server = false;
    bool get_user_location = false;
    bool all_automated = false;
    if (argc <= 1) {
        print_help();
        return -1;
    }
    while ((opt = getopt(argc, argv, ":u:d:hlba")) != -1) {
        switch (opt) {
            case 'h':
                print_help();
                return 0;
                break;
            case 'u':
                if (strlen(optarg) > 0) {
                    only_upload = true;
                    only_upload_host = malloc(strlen(optarg));
                    memcpy(only_upload_host, optarg, strlen(optarg));
                }
                break;
            case 'd':
                if (strlen(optarg) > 0) {
                    only_download = true;
                    only_download_host = malloc(strlen(optarg));
                    memcpy(only_download_host, optarg, strlen(optarg));
                }
                break;
            case 'l':
                get_user_location = true;
                break;
            case 'b':
                get_best_server = true;
                break;
            case 'a':
                all_automated = true;
            case ':':
                printf("Error. Argument needed for -%c option.\n", optopt);
                if (strlen(only_upload_host) != 0) {
                    free(only_upload_host);
                }
                if (strlen(only_download_host) != 0) {
                    free(only_download_host);
                }

                print_help();
                return -1;
                break;
            case '?':
                printf("Error. Unknown -%c argument.\n", optopt);
                if (strlen(only_upload_host) != 0) {
                    free(only_upload_host);
                }
                if (strlen(only_download_host) != 0) {
                    free(only_download_host);
                }
                print_help();
                return -1;
                break;
            default:
                print_help();
                return 0;
                break;
        }
    }

    Response response;
    response.string = malloc(1);
    response.size = 0;
    
    CURL *curl;
    curl = curl_easy_init();

    if (all_automated == true) {
    
    }
    if (get_user_location == true) {
        printf("Getting user's geolocation...");
        response = get_geo_response(curl, &response);
        if (response.size != 0) {
            printf(" OK.\n");
            cJSON *country = cJSON_Parse(response.string);
            char *country_name = cJSON_GetObjectItem(country, "country")->valuestring;
            char *country_code = cJSON_GetObjectItem(country, "countryCode")->valuestring;
            printf("RESULTS\n----------\nCountry: %s (country code: %s)\n", country_name, country_code);
            cJSON_Delete(country);
        }
        else {
            printf("RESULTS\n----------\nFailed to get user geo location.\n");
        }
    }
    if (only_upload == true) {
    
    }
    if (only_download == true) {
    
    }
    if (get_best_server == true) {
    
    }

    if (strlen(only_upload_host) != 0) {
        free(only_upload_host);
    }
    if (strlen(only_download_host) != 0) {
        free(only_download_host);
    }
    free(response.string);
    curl_easy_cleanup(curl);
    return 0;
    int result;
    for (int i=0; i<num_of_objects; i++) {
        server = cJSON_GetArrayItem(root, i);
        cJSON_AddItemToObject(server, "download_speed", cJSON_CreateNumber(0));
        cJSON_AddItemToObject(server, "upload_speed", cJSON_CreateNumber(0));
        cJSON_AddItemToObject(server, "temp_host_name", cJSON_CreateString(cJSON_GetObjectItem(server, "host")->valuestring));
    }
    for (int i=0; i<num_of_objects; i++) {
        server = cJSON_GetArrayItem(root, i);
        printf("Testing [%04d/%d]: %50s",i+1, num_of_objects+1, cJSON_GetObjectItem(server, "host")->valuestring);
        //curl_easy_setopt(curl, CURLOPT_URL, strcat(cJSON_GetObjectItem(server, "temp_host_name")->valuestring, "/random10x10.jpg"));
        curl_easy_setopt(curl, CURLOPT_URL, cJSON_GetObjectItem(server, "host")->valuestring);
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, dummy_write);
        curl_easy_setopt(curl, CURLOPT_TIMEOUT, 15L);
        curl_easy_setopt(curl, CURLOPT_NOBODY, 1L);
        curl_easy_setopt(curl, CURLOPT_USERAGENT, "C server speed test");
        result = curl_easy_perform(curl);
        if (result != CURLE_OK) {
            printf("%s (%s)\n", "...ERROR.", curl_easy_strerror(result));
        }
        else {
            //curl_off_t download_speed;
            double connect_speed;
            printf("%s", "...OK");
            //result = curl_easy_getinfo(curl, CURLINFO_SPEED_DOWNLOAD_T, &download_speed);
            //if (result == CURLE_OK) {
            //    cJSON_AddNumberToObject(server, "download_speed", download_speed);
            //}
            result = curl_easy_getinfo(curl, CURLINFO_CONNECT_TIME, &connect_speed);
            if (result == CURLE_OK) {
                printf(" (Connect time: %.10f)\n", connect_speed);
            }
        }
    }
    
   
    return 0;
}
size_t dummy_write(void *buffer, size_t size, size_t nmemb, void *userp){
   return size * nmemb;
}

size_t write_chunk(void *buffer, size_t size, size_t nmemb, void *userp){
    
    size_t real_size = size * nmemb;
    Response *response = (Response *) userp;
    char *ptr = realloc(response->string, response->size + real_size + 1);
    if (ptr == NULL) {
        return 0;
    }
    response->string = ptr;
    memcpy(&(response->string[response->size]), buffer, real_size);
    response->size += real_size;
    response->string[response->size] = '\0';
    return real_size;
}

Response get_geo_response(CURL *curl, Response *response){

    CURLcode result;
    curl_easy_setopt(curl, CURLOPT_URL, IP_GEO_API);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_chunk);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *) response);

    result = curl_easy_perform(curl);
    if (result != CURLE_OK) {
        printf(" ERROR. (%s)\n", curl_easy_strerror(result));
        *response->string=' ';
        return *response;
    }
    return *response;
}

void print_help(){
    printf("Usage: ./speed_test [OPTIONS]\n");
    printf("Options:\n");
    printf("\t-d <host>\tDo a download speed test for inputted host\n");
    printf("\t-u <host>\tDo an upload speed test for inputted host\n");
    printf("\t-b\t\tGet the best server by location\n");
    printf("\t-l\t\tFind the user location\n");
    printf("\t-a\t\tDo the full automated test\n");
    printf("\t-h\t\tPrint this help message\n");

}
