/*
 *
 * templat_main.c
 *	  template_main() routine for the executable.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "simple_c.h"
#include "template_main.h"

#define PROJ_VERSION 		"0.1.0"
#define PROJ_VERSIONSTR 		"Template Main " PROJ_VERSION
#define PROJ_BUILDSTR 		"Build " __DATE__ " " __TIME__
#define PROJ_EMAIL 			"jaimin.pan@gmail.com"

#define log_error printf


static int server_main(int argc, char* argv[]);
static void help(const char *progname);
static const char* get_progname(const char *argv0);
static void check_root(const char *progname);


TemplateMainOptionData template_main_option_data = {
	.usage_callback = help,
	.version = PROJ_VERSIONSTR "\n" PROJ_BUILDSTR,
};
TemplateMainOption template_main_option = &template_main_option_data;

TemplateMainGeneralData template_main_general_data;
TemplateMainGeneral template_main_general = &template_main_general_data;


static int
server_main(int argc, char* argv[])
{
	(void) argc, (void) argv;
	log_error("template main is called");

	return 0;
}

int
template_main(int argc, char *argv[], template_main_callback main_callback,
			  TemplateMainOption option)
{
	bool		do_check_root = true;

	if (!option)
		option = template_main_option;

	const char* progname = template_main_general->progname = get_progname(argv[0]);

	/*
	 * Catch standard options before doing much else, in particular before we
	 * insist on not being root.
	 */
	if (argc > 1)
	{
		if (strcmp(argv[1], "--help") == 0)
		{
			if (option->usage_callback)
				option->usage_callback(progname);
			else
				help(progname);
			exit(0);
		}
		if (strcmp(argv[1], "--version") == 0 || strcmp(argv[1], "-V") == 0)
		{
			if (option->version)
				printf("%s\n", option->version);
			else {
				fputs(PROJ_VERSIONSTR "\n", stdout);
				fputs(PROJ_BUILDSTR "\n", stdout);
			}
			exit(0);
		}

		/*
		 * In addition to the above, we allow "--debug"
		 * to be called by root.
		 */
		if (strcmp(argv[1], "--debug") == 0)
			do_check_root = false;
	}

	/*
	 * Make sure we are not running as root, unless it's safe for the selected
	 * option.
	 */
	if (do_check_root)
		check_root(progname);

	if (!main_callback)
		main_callback = server_main;
	return main_callback(argc, argv);
}


static void
help(const char *progname)
{
	printf(_("%s is server.\n\n"), progname);
	printf(_("Usage:\n  %s [OPTION]...\n\n"), progname);

	printf(_("Options:\n"));
	printf(_("  -p PORT            port number to listen on\n"));
	printf(_("  -V, --version      output version information, then exit\n"));
	printf(_("  --help             show this help, then exit\n"));

	printf(_("\nPlease read the documentation for the complete list of run-time\n"
			 "configuration settings and how to set them on the command line or in\n"
			 "the configuration file.\n\n"));
	printf(_("Report bugs to <%s>.\n"), PROJ_EMAIL);
}

static const char*
get_progname(const char *argv0)
{
	const char* progname = "Unknown";
	char sep = '/';
	char *p = strrchr(argv0, sep);
	if (p)
		progname = strdup(p + 1);

	return progname;
}

static void
check_root(const char *progname)
{
#ifndef WIN32
	if (geteuid() == 0)
	{
		log_error("\"root\" execution of the server is not permitted.\n"
					 "The server must be started under an unprivileged user ID to prevent\n"
					 "possible system security compromise.  See the documentation for\n"
					 "more information on how to properly start the server.\n");
		exit(1);
	}

	/*
	 * Also make sure that real and effective uids are the same. Executing as
	 * a setuid program from a root shell is a security hole, since on many
	 * platforms a nefarious subroutine could setuid back to root if real uid
	 * is root.  (Since nobody actually uses server as a setuid program,
	 * trying to actively fix this situation seems more trouble than it's
	 * worth; we'll just expend the effort to check for it.)
	 */
	if (getuid() != geteuid())
	{
		log_error("%s: real and effective user IDs must match\n",
					 progname);
		exit(1);
	}
#else							/* WIN32 */
	log_error("Checking for execution of server by a user \n"
			  "with administrative permissions is not implemented.\n");
#endif							/* WIN32 */
}
