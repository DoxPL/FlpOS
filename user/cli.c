#include "cli.h"
#include "std.h"
#include "memory.h"

static void builtin_echo(const char *[], uint8_t);
static void builtin_kernelinfo(const char *[], uint8_t);

static char line_buffer[CLI_LINE_BUFFER_SIZE];

typedef struct builtin_cmd_s {
    const char *cmd_name;
    void (*cmd_func_ptr)(const char*[], uint8_t);
} builtin_cmd_t;

static builtin_cmd_t builtin_array[CLI_BUILTIN_ARRAY_SIZE] = {
    //{ "if", builtin_if },
    { "echo", builtin_echo },
    { "kernelinfo", builtin_kernelinfo },
};

static void clear_line_buffer(void) {
    uint16_t i;
    for (i = 0; i < CLI_LINE_BUFFER_SIZE; i++) {
        line_buffer[i] = '\0';
    }
}

static void builtin_echo(const char *args[], uint8_t argc) {
    uint8_t i;
    if (argc > 0) {
        for (i = 0U; i < argc; i++) {
            printstr(args[i]);
            putchar(' ');
        }
    }
    putchar('\n');
}

static void builtin_kernelinfo(const char *args[], uint8_t argc) {
    (void) args;
    (void) argc;
    /* TODO: define kernel version */
    printstr("FLPOS-kernel-1.0");
    putchar('\n');
}

static void run_builtin_cmd(const char *cmd) {
    uint16_t builin_array_idx;
    uint32_t cmd_name_len;
    char *args[CLI_CMD_ARGS_MAX];
    uint8_t argc = 0U;
    bool_t cmd_found = false;
    char *cmd_token;

    if (cmd == NULL) {
        return;
    }

    cmd_token = stringtok(line_buffer, ' ');

    for (builin_array_idx = 0U;
        builin_array_idx < CLI_BUILTIN_ARRAY_SIZE; builin_array_idx++) {
        cmd_name_len = stringlen(builtin_array[builin_array_idx].cmd_name);
        if (stringcmp(cmd_token, builtin_array[builin_array_idx].cmd_name, \
            cmd_name_len) == 0) {
            cmd_found = true;
            break;
        }
    }

    if (cmd_found) {
            while ((cmd_token = stringtok(NULL, ' ')) != NULL) {
                args[argc++] = cmd_token;
            }
        cmd_token = stringtok(NULL, ' ');
        builtin_array[builin_array_idx].cmd_func_ptr((const char**)args, argc);
    } else {
        printstr("Command not found\n");
    }
}

static bool_t parse_line(void) {
    run_builtin_cmd(line_buffer);
    return false;
}

static void read_line(void) {
    uint16_t line_buffer_idx = 0U;
    uint8_t key;
    while (1) {
        key = kbrd_getkey();
        if (key == 0x13) {
            putchar('\n');
            line_buffer[line_buffer_idx] = '\0';
            break;
        } else if (key == 0x8) {
            putchar('\b');
            line_buffer_idx--;
        } else if (line_buffer_idx < CLI_LINE_BUFFER_SIZE) {
            line_buffer[line_buffer_idx++] = key;
            putchar(key);
        }
    }
}

static void run_cli(void) {
    while (1) {
        printstr("> ");
        read_line();
        parse_line();
        clear_line_buffer();
    }
}

void create_cli(void) {
    run_cli();
}
