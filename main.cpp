/*
Copyright (c) 2018 Yuriy Abramov (RegasenDev)

Permission is hereby granted, free of charge, to any person obtaining
a copy of6 this software and associated documentation files (the
"Software"), to deal in the Software without restriction, including
without limitation the rights to use, copy, modify, merge, publish,
distribute, sublicense, and/or sell copies of the Software, and to
permit persons to whom the Software is furnished to do so, subject to
the following conditions:

The above copyright notice and this permission notice shall be included
in all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY
CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE
SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
*/
#define HAVE_STDINT_H
#define _CRT_SECURE_NO_WARNINGS

#include "main.h" 

static size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

char* get_string(AMX* amx, cell param)
{
	int
		len = NULL,
		ret = NULL;

	cell *addr = NULL;

	amx_GetAddr(amx, param, &addr);
	amx_StrLen(addr, &len);

	if (len)
	{
		len++;

		char* text = new char[len];
		amx_GetString(text, addr, 0, len);

		return text;
	}
	return NULL;
}

cell AMX_NATIVE_CALL regasen_request_send(AMX* amx, cell* params)
{
	char* url = get_string(amx, params[3]);
	char* data = get_string(amx, params[4]);
	char* callback = get_string(amx, params[5]);

	int index = params[1];
	int type = params[2];

	CURL *curl;
	CURLcode res;

	long http_code = 0;
	int idx;

	curl = curl_easy_init();
	if (curl) {
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
		if (type == 2) {
			curl_easy_setopt(curl, CURLOPT_POST, 1);
			curl_easy_setopt(curl, CURLOPT_POSTFIELDS, data);
		}
		else {
			curl_easy_setopt(curl, CURLOPT_POST, 0);
		}
		curl_easy_setopt(curl, CURLOPT_URL, url);

		res = curl_easy_perform(curl);
		curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &http_code);
		curl_easy_cleanup(curl);

		if (!amx_FindPublic(amx, callback, &idx))
		{
			cell
				ret,
				addr;

			amx_PushString(amx, &addr, NULL, response.c_str(), NULL, NULL);


			amx_Push(amx, http_code);
			amx_Push(amx, index);

			amx_Exec(amx, &ret, idx);

			amx_Release(amx, addr);

			response = "";
		}
	}

	return 1;
}
PLUGIN_EXPORT unsigned int PLUGIN_CALL Supports()
{
	return SUPPORTS_VERSION | SUPPORTS_AMX_NATIVES;
}

PLUGIN_EXPORT bool PLUGIN_CALL Load(void **ppData)
{
	pAMXFunctions = ppData[PLUGIN_DATA_AMX_EXPORTS];
	logprintf = (logprintf_t)ppData[PLUGIN_DATA_LOGPRINTF];

	logprintf(" * Regasen HTTP loaded.");
	return true;
}

PLUGIN_EXPORT void PLUGIN_CALL Unload()
{
	logprintf(" * Regasen HTTP unloaded.");
}

AMX_NATIVE_INFO PluginNatives[] =
{
	{ "regasen_request_send", regasen_request_send },
	{ 0, 0 }
};

PLUGIN_EXPORT int PLUGIN_CALL AmxLoad(AMX *amx)
{
	return amx_Register(amx, PluginNatives, -1);
}


PLUGIN_EXPORT int PLUGIN_CALL AmxUnload(AMX *amx)
{
	return AMX_ERR_NONE;
}
