/*
 * main.c
 */

#include "template_main.h"
#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "signal.h"
#include "time.h"
#include "unistd.h"

#define _(x) x

#define PROJ_VERSIONSTR 		"Test Server 1.0"
#define PROJ_BUILDSTR 		"Build " __DATE__ " " __TIME__
#define PROJ_EMAIL 			"jaimin.pan@gmail.com"

static int server_main(int argc, char *argv[]);
static void usage(const char *progname);

TemplateMainOptionData my_template_main_option_data = {
	.usage_callback = usage,
	.version = PROJ_VERSIONSTR "\n" PROJ_BUILDSTR
};

static int
server_main(int argc, char *argv[])
{
	int			errs = 0;
	int			flag;
	int			procPid;
	long		startTime;

	const char* configFile = NULL;
	const char* host = NULL;
	int			port = 0;

	procPid = getpid();

	startTime = time(NULL);

	/*
	 * Initialize random(3) so we don't get the same values in every run.
	 */
	srand((unsigned int) (procPid ^ startTime));

	signal(SIGPIPE, SIG_IGN);

	/*
	 * Parse command-line options.
	 * the common help() function in main/main.c.
	 */
	while ((flag = getopt(argc, argv, "f:h:ip:")) != -1)
	{
		switch (flag)
		{
			case 'f':
				configFile = strdup(optarg);
				break;
			case 'h':
				host = strdup(optarg);
				break;
			case 'i':
				host = strdup("0.0.0.0");
				break;
			case 'p':
				port = atoi(optarg);
				break;
			default:
				errs++;
				break;
		}

		if (errs)
			break;
	}

	if (errs) {
		return -1;
	}

	printf("server main start\n");
	for (int i=0; i<argc; i++)
		printf("args is %s\n", argv[i]);

	printf("\n");
	printf("Using config file '%s'\n", configFile);
	printf("%s now ready to accept connections on '%s:%d'\n",
			template_main_general->progname,
			host, port);

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

	printf(_("\nReport bugs to <%s>.\n"), PROJ_EMAIL);
}

int
main(int argc, char *argv[])
{
	return template_main(argc, argv, server_main, &my_template_main_option_data);
}
