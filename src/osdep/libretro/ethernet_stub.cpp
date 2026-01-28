#include "sysconfig.h"
#include "ethernet.h"

struct autoconfig_info;

bool ethernet_enumerate(struct netdriverdata **ndd, int)
{
	if (ndd) {
		*ndd = nullptr;
	}
	return false;
}

void ethernet_enumerate_free(void)
{
}

void ethernet_close_driver(struct netdriverdata *)
{
}

int ethernet_getdatalength(struct netdriverdata *)
{
	return 0;
}

int ethernet_open(struct netdriverdata *, void *, void *, ethernet_gotfunc *, ethernet_getfunc *, int, const uae_u8 *)
{
	return 0;
}

void ethernet_close(struct netdriverdata *, void *)
{
}

void ethernet_trigger(struct netdriverdata *, void *)
{
}

bool ethernet_getmac(uae_u8 *, const TCHAR *)
{
	return false;
}
