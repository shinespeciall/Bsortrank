#include "httpsServer.h"

httpsServer::httpsServer(std::string url, std::string path) : surl(url), spath(path)
{
	size_t urlsize = url.size();
	_url = new char[urlsize + 1];
	size_t pathsize = path.size();
	_path = new char[pathsize + 1];
	memset(_url, 0, urlsize + 1);
	memset(_path, 0, pathsize + 1);
	strcpy(_url, url.c_str());
	strcpy(_path, path.c_str());
}

httpsServer::~httpsServer()
{
	if (connectionfailure == 1) goto onlyCleanupWSA;
	SSL_shutdown(sslHandle);
	SSL_free(sslHandle);
	SSL_CTX_free(sslContext);
	closesocket(sock);
onlyCleanupWSA:
	WSACleanup();
	delete[] _url;
}

bool httpsServer::TCPconnect()
{
	WSADATA wsadata;
	if (0 != WSAStartup(MAKEWORD(2, 2), &wsadata)) return false;
	sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock == INVALID_SOCKET) return false;
	hostent *p = gethostbyname(_url);

	sockaddr_in sa;
	memcpy(&sa.sin_addr, p->h_addr, 4);
	sa.sin_family = AF_INET;
	sa.sin_port = htons(443);

	if (SOCKET_ERROR == connect(sock, (sockaddr*)&sa, sizeof(sockaddr))) return false;
	return true;
}

bool httpsServer::SSL_Connect()
{
	ERR_load_BIO_strings();
	SSL_library_init();
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	sslContext = SSL_CTX_new(SSLv23_client_method());
	if (sslContext == NULL) return false;
	// Create an SSL struct for the connection
	sslHandle = SSL_new(sslContext);
	if (sslHandle == NULL) return false;
	// Connect the SSL struct to our connection
	if (!SSL_set_fd(sslHandle, sock)) return false;
	// Initiate SSL handshake
	if (SSL_connect(sslHandle) != 1) return false;
	return true;
}

bool httpsServer::GetPage()
{
	std::string request;
	request = "GET " + spath + " HTTP/1.1\r\n" +"Host: " + surl + "\r\n" + "Connection:Close\r\n\r\n";
	char *pbuffer = new char[request.size()];
	strcpy(pbuffer, request.c_str());
	SSL_write(sslHandle, pbuffer, sizeof(pbuffer));
}
