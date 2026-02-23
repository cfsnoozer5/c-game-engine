#include "logger.h"
#include "asserts.h"
#include "platform/platform.h"

// Temp
#include <stdio.h>
#include <string.h>
#include <stdarg.h>

typedef struct logger_system_state {
    b8 initialized;
} logger_system_state;

static logger_system_state* state_ptr;

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}

b8 intialize_logging(u64* memory_requirement, void* state) {
    *memory_requirement = sizeof(logger_system_state);
    if (state == 0) {
        return true;
    }

    state_ptr = state;
    state_ptr->initialized = true;

    // Test it for now
    CFATAL("A test message: %f", 3.14f);
    CERROR("A test message: %f", 3.14f);
    CWARN("A test message: %f", 3.14f);
    CINFO("A test message: %f", 3.14f);
    CDEBUG("A test message: %f", 3.14f);
    CTRACE("A test message: %f", 3.14f);

    // TODO: create log file.

    return true;
}

void shutdown_logging(void* state) {
    state_ptr = 0;
}

void log_output(log_level level, const char* message, ...) {
    const char* level_strings[6] = {"FATAL", "ERROR", "WARN", "INFO", "DEBUG", "TRACE"};
    b8 is_error = level < LOG_LEVEL_WARN;

    // Static allocation for now, faster than malloc
    const i32 msg_legnth = 32000;
    char out_message[msg_legnth];
    memset(out_message, 0, sizeof(out_message));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    vsnprintf(out_message, msg_legnth, message, arg_ptr);
    va_end(arg_ptr);
    
    char p_message[msg_legnth];
    sprintf(p_message, "[%s]: %s\n", level_strings[level], out_message);

    // Platform-specific output.
    if (is_error) {
        platform_console_write_error(p_message, level);
    } else {
        platform_console_write(p_message, level);
    }
}

