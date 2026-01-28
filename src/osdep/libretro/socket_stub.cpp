#include "sysconfig.h"
#include "uae/socket.h"

bool uae_socket_init(void)
{
	return false;
}

uae_socket uae_socket_accept(uae_socket)
{
	return UAE_SOCKET_INVALID;
}

int uae_socket_read(uae_socket, void *, int)
{
	return -1;
}

int uae_socket_write(uae_socket, const void *, int)
{
	return -1;
}

int uae_socket_select(uae_socket, bool, bool, bool, uae_u64)
{
	return 0;
}

bool uae_socket_close(uae_socket)
{
	return true;
}

int uae_socket_error(void)
{
	return -1;
}

uae_socket uae_tcp_listen(const TCHAR *, const TCHAR *, int)
{
	return UAE_SOCKET_INVALID;
}

uae_socket uae_tcp_listen_uri(const TCHAR *, const TCHAR *, int)
{
	return UAE_SOCKET_INVALID;
}

const TCHAR *uae_uri_path(const TCHAR *p)
{
	return p ? p : _T("");
}
