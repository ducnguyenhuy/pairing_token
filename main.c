#include <stdio.h>
#include <string.h>
#include "https.h"

int main(int argc, char *argv[])
{
    HTTP_INFO hi;
    char response[4096];
    char data[1024];
    int ret;

    // Initialize HTTPS session with certificate verification
    http_init(&hi, TRUE);

    // Prepare the JSON request data
    snprintf(data, sizeof(data),
        "{"
        "\"clientId\":\"670e4eb5aa58ac3dbb25a145\","
        "\"clientKey\":\"61051de7a219d8a321b93c9b872d2ddc\","
        "\"clientSecret\":\"e273a856accc2afb4c30fa792e50a805\","
        "\"moveCard\":8"
        "}"
    );

    printf("Sending request to: https://stg-cam.viettel.io/project/api/public/v1/project/calSignature\n");
    printf("Request data: %s\n", data);

    // Make the POST request to the calSignature endpoint
    ret = http_post(&hi, 
        "https://stg-cam.viettel.io/project/api/public/v1/project/calSignature",
        data,
        response,
        sizeof(response)
    );

    if (ret < 0) {
        char error_msg[1024];
        http_strerror(error_msg, sizeof(error_msg));
        printf("Error making request: %s\n", error_msg);
    } else {
        printf("Response status code: %d\n", ret);
        printf("Response body: %s\n", response);
    }

    // Clean up
    http_close(&hi);

    return 0;
}
