/*
 * main.c
 */

#include "template_main.h"
#include "stdio.h"

#define _(x) x

static int
server_main(int argc, char *argv[])
{
	printf("server main start\n");
	return 0;
}

static void
usage(const char *progname)
{
	printf(_("%s is test program.\n\n"), progname);
	printf(_("Usage:\n  %s [OPTION]...\n\n"), progname);

	printf(_("Options:\n"));
	printf(_("  -p PORT            port number to listen on\n"));
	printf(_("  -V, --version      output version information, then exit\n"));
	printf(_("  --help             show this help, then exit\n"));
}

int
main(int argc, char *argv[])
{
	return template_main(argc, argv, server_main, usage);
}
