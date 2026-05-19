
#include <curl/curl.h>
#include <cjson/cJSON.h>

#include <stdio.h>
#include <stdlib.h>
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
    cJSON *host;
    if (root == NULL) {
        const char *error_ptr = cJSON_GetErrorPtr();
        if (error_ptr != NULL) {
            printf("Error parsing JSON file: %s\n", error_ptr);
        }
        //cJSON_Delete(root);
        return -2;
    }
    int num_of_objects = cJSON_GetArraySize(root);
    cJSON *hosts_arr = cJSON_CreateArray();
    for (int i=0; i<num_of_objects; i++) {
        server = cJSON_GetArrayItem(root, i);
        host = cJSON_GetObjectItem(server, "host");
        cJSON_AddItemToArray(hosts_arr, host);
    }
    for (int i=0; i<num_of_objects; i++) {
        printf("Server %d url: %s\n", i, cJSON_GetArrayItem(hosts_arr, i)->valuestring);
    }
    //cJSON_Delete(root);
    free(file_buffer);
    return 0;
    CURL *curl;
    curl = curl_easy_init();
    printf("Hello world!\n");
    curl_easy_cleanup(curl);
    return 0;
}
