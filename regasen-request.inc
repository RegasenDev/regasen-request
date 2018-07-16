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
 
#if !defined REGASEN_REQUEST_INC_
    #define REGASEN_REQUEST_INC_
	#if !defined HTTP
		#define HTTP_GET						1
		#define HTTP_POST						2
	#endif

	#define HTTP_RESPONSE_OK 200
	#define HTTP_RESPONSE_BAD_REQUEST 400
	#define HTTP_RESPONSE_NOT_FOUND 404
	#define HTTP_RESPONSE_SERVER_ERROR 500
	#define HTTP_RESPONSE_BAD_GATEWAY 502
		
	native regasen_request_send(index, type, url[], data[], callback[]);

#endif

/**
	Example:
	public OnGameModeInit()
	{
		regasen_request_send(
			1,
			HTTP_POST,
			"https://api.vk.com/method/users.get",
			"user_ids=1",
			"ResponseCallback"
		);
		return 1;
	}

	forward ResponseCallback(playerid, response_code, data[]);
	public ResponseCallback(playerid, response_code, data[])
	{
		printf("%d %s", playerid, data);
		return true;
	}
**/
