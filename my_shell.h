#ifndef MY_SHELL_H_
#define MY_SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

#define CMD_NORM 0
#define CMD_OR 1
#define CMD_AND 2
#define CMD_CHAIN 3

#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
 * struct liststr - singly-linked list definition
 * @num: number field
 * @str: textual string data
 * @next: reference to the following/next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 * struct passinfo - define pseudo-arguments which will pass into a func,
 * establishes a consistent prototype for a ptr-function struct.
 * @arg: String containing arguments (gotten from get_line)
 * @argv: Array of strings (gotten from 'arg')
 * @path: A string representing the path for the current command
 * @argc: The count of arguments
 * @line_count:To keep track of error couns.
 * @err_num: Error code for any 'exit()'
 * @linecount_flag: checks if line of input is valid
 * @fname: file name
 * @env: local copy of _environ (linked_list)
 * @environ: Custom made _enviro (linked_list)
 * @history: Node for the history
 * @alias: Alias' node
 * @env_changed: Indicates whether _environ was edited
 * @status: The status of the command last executed
 * @cmd_buf: Contains address of pointer to command_buffer
 * @cmd_buf_type: Represents the command_type (||, &&, ;)
 * @readfd: The File descriptor used to read line input
 * @histcount: Count of history line numbers
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf;
	int cmd_buf_type;
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT                            \
	{                                                                           \
		NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
			0, 0, 0                                                             \
	}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function program will execute
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* my_atoi.c */
int interactive_mode(info_t *);
int delimeter(char, char *);
int _alpha(int);
int _stin(char *);

/* my_shproc.c */
int hsh(info_t *, char **);
int _fdbutin(info_t *);
void fd_n_exe_cmd(info_t *);
void fk_n_exe_cmd(info_t *);

/* path_resolution.c */
int _execmd(info_t *, char *);
char *_chdupt(char *, int, int);
char *_fdcmd_pth(info_t *, char *, char *);

int loophsh(char **);

/* my_errhan.c */
void _dputss(char *);
int _stderr(char);
int _printFd(char c, int fd);
int _outputStr(char *str, int fd);

/* str.c */
int my_lenstr(char *);
int comp_strs(char *, char *);
char *f_sbstr(const char *, const char *);
char *combined_strings(char *, char *);

/* my_strupd.c */
char *_cpy_str(char *, char *);
char *_strdup(const char *);
void _puts(char *);
int _putchar(char);

/* strspl.c */
char **_strSplit_(char *, char *);
char **_str_Split2(char *, char);

/* my_ext_string_ops.c */
char *_cpstr(char *, char *, int);
char *_catstr(char *, char *, int);
char *_chstr(char *, char);

/* my_realloc.c */
char *ctm_mset(char *, char, unsigned int);
void _frstrarray(char **);
void *_ctm_rlloc(void *, unsigned int, unsigned int);

/* my_memman.c */
int fr_n_null(void **);

/* my_errhan.c */
int stderrtoi(char *);
void _emessage(info_t *, char *);
int _odec(int, int);
char *_cnum(long int, int, int);
void _crem(char *);

/* my_builtin.c */
int _sExit(info_t *);
int _sDir(info_t *);
int _sHelp(info_t *);

/* my_builtin1.c */
int _History(info_t *);
int _ALIAS(info_t *);

/*my_getline.c */
ssize_t _gtInp(info_t *);
int ctm_gtline(info_t *, char **, size_t *);
void sig_intHandler(int);

/* info_man.c */
void _initialinfo(info_t *);
void _setInfo_(info_t *, char **);
void _relinfo(info_t *, int);

/* my_envut.c */
char *Env_var(info_t *, const char *);
int pEnv(info_t *);
int sEnv_var(info_t *);
int unEnv_var(info_t *);
int pEnv_ls(info_t *);

/* my_getenv.c */
char **gEnv(info_t *);
int _unEnv(info_t *, char *);
int sEnv(info_t *, char *, char *);

/* my_hismang.c */
char *_gthist_fpath(info_t *info);
int sv_hist_file(info_t *info);
int _rhistory(info_t *info);
int _add_hist_list(info_t *info, char *buf, int linecount);
int rfrsh_hist_numbs(info_t *info);

/* my_ltops.c */
list_t *_adnode(list_t **, const char *, int);
list_t *_appendnode(list_t **, const char *, int);
size_t p_strlist(const list_t *);
int eliminate_node_at_index(list_t **, unsigned int);
void _emplist(list_t **);

/* my_ltopsup.c */
size_t lt_lth(const list_t *);
char **_string_listarray(list_t *);
size_t _disp_list(const list_t *);
list_t *_nde_srt_fder(list_t *, char *, char);
ssize_t gt_nde_pst(list_t *, list_t *);

/* my_manistr.c */
int chk_chn_del(info_t *, char *, size_t *);
void chk_chn_cnd(info_t *, char *, size_t *, size_t, size_t);
int _repalias(info_t *);
int _repvar(info_t *);
int repStrs(char **, char *);

#endif /* MY_SHELL_H */

