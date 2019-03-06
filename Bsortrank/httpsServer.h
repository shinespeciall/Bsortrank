#pragma once
#include <Windows.h>
#include <stdio.h>
#include <string.h>
#include <string>

#include <regex>
#include <urlmon.h>

#include <openssl/rand.h>
#include <openssl/ssl.h>
#include <openssl/err.h>

#pragma comment(lib, "urlmon.lib")
#pragma comment( lib, "libeay32.lib" )
#pragma comment( lib, "ssleay32.lib" )

#pragma comment(lib, "WS2_32.lib")

class httpsServer
{
public:
	httpsServer(std::string url, std::string path);
	~httpsServer();
private:
	char *_url;
	char *_path;
	std::string surl;
	std::string spath;
	SOCKET sock;
	SSL *sslHandle;
	SSL_CTX *sslContext;
	BIO *bio;
	int connectionfailure = 0;
	bool TCPconnect();
	bool SSL_Connect();
	bool GetPage();
};

