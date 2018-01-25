#ifndef TEMPLATE_MAIN_H
#define TEMPLATE_MAIN_H

extern const char *progname;

typedef int (*template_main_callback) (int argc, char *argv[]);

typedef void (*template_usage_cllback) (const char *progname);

extern int template_main(int argc, char *argv[],
						template_main_callback main_callback,
						template_usage_cllback usage_callback);


#endif /* TEMPLATE_MAIN_H */
