#include <string>
#include <curl/curl.h> 

#include "SDK/amx/amx.h" 
#include "SDK/plugincommon.h"

typedef void(*logprintf_t)(char* format, ...);

logprintf_t logprintf;
extern void *pAMXFunctions;
static std::string response;
char* get_string(AMX* amx, cell param);
static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp);

using namespace std;