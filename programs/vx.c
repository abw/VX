#include <vx.h>
#include <getopt.h>
#include <readline/readline.h>
#include <readline/history.h>


#define VX_OPTION_SIG     "vdhtqr:f:e:"
#define VX_QUIT           "quit"
#define VX_EXIT           "exit"
#define VX_EXPR_PROMPT    VX_ANSI_CYAN "expr> " VX_ANSI_RESET
#define VX_TEST_PROMPT    VX_ANSI_CYAN "test> " VX_ANSI_RESET
#define VX_BAD_COMMAND    "Unknown command: %s     (type 'help' for help)"

void        vx_banner();
void        vx_info(VX);
void        vx_help();
void        vx_say(char *format, ...);
void        vx_warn(char *format, ...);
void        vx_getopt(VX vx, int argc, char **argv);
void        vx_interactive(VX vx);
VXString    vx_prompt_init();
void        vx_prompt_free();
VXString    vx_input_read(VXString prompt);
void        vx_input_free();
char **     vx_completion(const char *, int, int);
char *      vx_command_generator(const char *, int);

VXBool      vx_cmd_todo(VX, VXString);
VXBool      vx_cmd_delta(VX, VXString);
VXBool      vx_cmd_epsilon(VX, VXString);
VXBool      vx_cmd_yalgeth(VX, VXString);
VXBool      vx_cmd_help(VX, VXString);
VXBool      vx_cmd_quit(VX, VXString);

static int be_quiet  = 0;
static int read_text = 0;
static VXString vx_input  = NULL;
static VXString vx_prompt = NULL;      /* old way */


static struct option vx_options[] = {
    {"execute",  required_argument,  NULL, 'e' },
    {"quiet",    no_argument,        NULL, 'q' },
    {"verbose",  no_argument,        NULL, 'v' },
    {"debug",    no_argument,        NULL, 'd' },
    {"help",     no_argument,        NULL, 'h' },
    {"file",     required_argument,  NULL, 'f' },
    {"badger",   no_argument,        NULL, 'b' },
    {"mushroom", required_argument,  NULL, 'm' },
    {"snake",    required_argument,  NULL, 's' },
    {0, 0, 0, 0}
};

typedef struct {
    VXBool   (*func)(VX, VXString);
    VXString    name;
    VXString    about;
} vx_command;

vx_command vx_commands[] = {
    { &vx_cmd_todo,   "expr",   "Evaluate a single vx expression"           },
    { &vx_cmd_todo,   "data",   "Load VX data specification from a file"    },
    { &vx_cmd_todo,   "text",   "Process some document text"                },
    { &vx_cmd_todo,   "test",   "Run a vx test script"                      },
    { &vx_cmd_delta,  "delta",  "Transmute a delta vector"                  },
    { &vx_cmd_help,   "help",   "Help on using vx"                          },
    { &vx_cmd_quit,   "quit",   "Quit using vx"                             },
    { NULL, NULL, NULL }
};

vx_command * execute = NULL;
int exit_val = 0;

vx_command *vx_command_lookup_or_die(VXString name);
vx_command *vx_command_lookup(VXString name);



#define vx_nl()                           \
    fprintf(stderr, "\n");

#define vx_verbose(vx, format, ...)     \
    if (vx->verbose) vx_say(format, ##__VA_ARGS__)




/*--------------------------------------------------------------------------
 * main entry point
 *--------------------------------------------------------------------------*/

int main(
    int  argc, 
    char **argv, 
    char **env
) {
    VX          vx = VX_new();
    VXString    filename;
    int         result = 0;
    
    vx_prompt_init();
    vx_getopt(vx, argc, argv);

    if (! be_quiet)
        vx_banner();
    
    if (vx->verbose)
        vx_info(vx);

    if (execute) {
        // vx_debug_msg("run %s command with arg: %s\n", execute->name, optind < argc ? argv[optind] : "NULL");
        execute->func(vx, optind < argc ? argv[optind++] : NULL);
        result = exit_val;   /* hack to allow tests to define exit value */
    }
    else if (optind < argc) {
        if (read_text) {
            vx_fatal("Unstable resonator detected.  Advise immediate shutdown");
        }
        else {
            while (optind < argc) {
                filename = argv[optind++];
                vx_debug_msg(vx, "loading file: %s", filename);
                vx_debug_msg("invalid data format: %s", filename);
            }
        }
    }
    else {
        vx_interactive(vx);
    }
        
    vx_prompt_free();
    VX_free(vx);

    return result;
}



/*--------------------------------------------------------------------------
 * interactive mode
 *--------------------------------------------------------------------------*/

vx_command *
vx_command_lookup_or_die(
    VXString name
) {
    vx_command * cmd = vx_command_lookup(name);
    if (! cmd) {
        vx_warn(VX_BAD_COMMAND, name);
        exit(1);
    }
    return cmd;
}



vx_command *
vx_command_lookup(
    VXString name
) {
    int i;
    
    for (i = 0; vx_commands[i].name; i++) {
        if (strcmp(name, vx_commands[i].name) == 0) {
            return &vx_commands[i];
        }
    }

    return NULL;
}


void vx_interactive(
    VX vx
) {
    VXString prompt = vx_prompt;
    VXBool   done   = VX_FALSE;
    VXString input, args;
    vx_command *cmd;

    rl_readline_name = VX_STR_VX;
    rl_completion_entry_function = (Function *) &vx_command_generator;

    while(! done) {
        input = vx_input_read(prompt);
        
        if (! input) {
            fprintf(stderr, " %s[exit]%s\n", VX_ANSI_BLUE, VX_ANSI_RESET);
            break;
        }

        cmd  = vx_command_lookup_or_die(input);
        done = cmd->func(vx, args);
    }

    vx_input_free();

    return;
}



/* TODO: colour should be a configuration/runtime option */

void vx_banner() {
    fprintf(
        stderr, "%s%s v%s %s by %s %s%s\n",
        VX_ANSI_YELLOW,
        VX_NAME,
        VX_VERSION,
        VX_ARCHITECTURE,
        VX_AUTHOR,
        VX_EMAIL,
        VX_ANSI_RESET
    );
}

void vx_info(
    VX vx
) {
    VXString dir = VX_DIR;

    fprintf(
        stderr, "%svx.dir: %s%s%s\n",
        VX_ANSI_YELLOW,
        VX_ANSI_CYAN,
        dir,
        VX_ANSI_RESET
    );
}


/*--------------------------------------------------------------------------
 * input
 *--------------------------------------------------------------------------*/

VXString
vx_prompt_init() {
    if (! vx_prompt) {
        asprintf(
            &vx_prompt, "%s%s>%s ",
            VX_ANSI_CYAN, VX_PROMPT,VX_ANSI_RESET
        );
    }
    return vx_prompt;
}

void
vx_prompt_free() {
    if (vx_prompt) {
        free(vx_prompt);
        vx_prompt = NULL;
    }
}


VXString
vx_input_read(
    VXString prompt
) {
    vx_input_free();

    vx_input = readline(prompt);
    
    if (vx_input) {
        if (*vx_input)
            add_history(vx_input);
    }

    return vx_input;
}


char **
vx_completion(
    const char *text, 
    int start, 
    int end
) {
    return rl_completion_matches(text, &vx_command_generator);
}


char *
vx_command_generator(
    const char *text,
    int state
) {
    static int list_index, len;
    char *name;

    /* If this is a new word to complete, initialize now.  This includes
        saving the length of TEXT for efficiency, and initializing the index
        variable to 0. */
    if (! state) {
        list_index = 0;
        len = strlen(text);
    }

    /* Return the next name which partially matches from the command list. */
    while ((name = vx_commands[list_index].name)) {
        list_index++;

        if (strncmp(name, text, len) == 0)
            return strdup(name);
    }

    return NULL;
}


void
vx_input_free() {
    if (vx_input) {
        free (vx_input);
        vx_input = NULL;
    }
}


void vx_say(
    char *format, ...
) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "%s", vx_prompt);
    vfprintf(stderr, format, args);
    fprintf(stderr, "\n");
    va_end(args);
}

void vx_warn(
    char *format, ...
) {
    va_list args;
    va_start(args, format);
    fprintf(stderr, "%svx> ", VX_ANSI_RED);
    vfprintf(stderr, format, args);
    fprintf(stderr, "%s\n", VX_ANSI_RESET);
    va_end(args);
}



/*--------------------------------------------------------------------------
 * commands
 *--------------------------------------------------------------------------*/

VXBool 
vx_cmd_todo(
    VX     vx, 
    VXString input
) {
    vx_warn("Sorry, that functionality is still TODO");
    return VX_FALSE;
}

VXBool 
vx_cmd_delta(
    VX     vx, 
    VXString input
) {
    vx_warn("Sorry, you are not authorised to modify the delta function");
    return VX_FALSE;
}


VXBool 
vx_cmd_help(
    VX     vx, 
    VXString input
) {
    int i;
    vx_command cmd;
    printf("VX commands:\n");
    
    for (i = 0; vx_commands[i].name; i++) {
        cmd = vx_commands[i];
        printf(
            "      %s%-12s %s%s%s\n", 
            VX_ANSI_CYAN, 
            cmd.name, 
            VX_ANSI_YELLOW, 
            cmd.about, 
            VX_ANSI_RESET
        );
    }
    return VX_FALSE;
}


VXBool 
vx_cmd_quit(
    VX     vx, 
    VXString input
) {
    return VX_TRUE;
}


/*--------------------------------------------------------------------------
 * options and help
 *--------------------------------------------------------------------------*/

void
vx_getopt(
    VX   vx,
    int         argc,
    char        **argv
) {
    int opt;
    int ndx = 0;

    while (1) {
        opt = getopt_long(argc, argv, VX_OPTION_SIG, vx_options, &ndx);

        if (opt == -1)
            break;

        switch (opt) {
            case 0:
                /* currently not used */
                printf ("option %s", vx_options[ndx].name);
                if (optarg)
                    printf (" with arg %s", optarg);
                printf ("\n");
                break;

            case 'v':
                vx->verbose = VX_TRUE;
                break;

            case 'd':
                vx->debug = VX_TRUE;
                break;

            case 'e':
                execute = vx_command_lookup_or_die(optarg);
                break;

            case 't':
                read_text = 1;
                break;

            case 'q':
                be_quiet = 1;
                break;

            case 'f':
                break;

            case 'r':
                break;

            case 'h':
                vx_banner();
                vx_help();
                exit(42);

            case '?':
                fprintf(stderr, "Type '%s --help' for help\n", VX_NAME);
                
            default:
                exit(69);
                break;
        }
    }
}


void vx_help() {
    fprintf(
        stderr,
        "\nUsage:\n"
        "    %s [options] file1 file2 ... file<n>\n", 
        VX_NAME
    );
    fprintf(
        stderr,
        "\nOptions:\n"
        "    -e cmd  --execute cmd       execute command\n"
        "    -t      --text              read text from comment line arguments\n"
        "    -q      --quiet             quiet mode - no messages\n"
        "    -v      --verbose           enable verbose messages\n"
        "    -r      --root              vx root directory (default: %s)\n"
        "    -d      --debug             enable debugging messages\n"
        "    -h      --help              this help\n",
        VX_DIR
    );
}

