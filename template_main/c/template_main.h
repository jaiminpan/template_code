#ifndef TEMPLATE_MAIN_H
#define TEMPLATE_MAIN_H


typedef int (*template_main_callback) (int argc, char *argv[]);

typedef void (*template_usage_cllback) (const char *progname);

typedef struct template_main_option
{
	template_usage_cllback usage_callback;
	const char *version;
} TemplateMainOptionData;

typedef TemplateMainOptionData *TemplateMainOption;

extern TemplateMainOptionData template_main_option_data;
extern TemplateMainOption template_main_option;

typedef struct template_main_general
{
	const char *progname;
} TemplateMainGeneralData;

typedef TemplateMainGeneralData *TemplateMainGeneral;

extern TemplateMainGeneralData template_main_general_data;
extern TemplateMainGeneral template_main_general;


extern int template_main(int argc, char *argv[], template_main_callback main_callback,
						 TemplateMainOption options);



#endif /* TEMPLATE_MAIN_H */
