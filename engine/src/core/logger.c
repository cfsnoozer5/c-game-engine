#include "logger.h"
#include "asserts.h"

#include "platform/platform.h"
#include "platform/filesystem.h"

#include "core/cstring.h"
#include "core/cmemory.h"

#include <stdarg.h>

typedef struct logger_system_state {
    file_handle log_file_handle;
} logger_system_state;

static logger_system_state* state_ptr;

void append_to_log_file(const char* msg) {
    if (state_ptr && state_ptr->log_file_handle.is_valid) {
        u64 length = string_length(msg);
        u64 written = 0;
        if (!file_write(&state_ptr->log_file_handle, length, msg, &written)) {
            platform_console_write_error("ERROR writing to console.log", LOG_LEVEL_ERROR);
        }
    }
}

void report_assertion_failure(const char* expression, const char* message, const char* file, i32 line) {
    log_output(LOG_LEVEL_FATAL, "Assertion Failure: %s, message: '%s', in file: %s, line: %d\n", expression, message, file, line);
}

b8 intialize_logging(u64* memory_requirement, void* state) {
    *memory_requirement = sizeof(logger_system_state);
    if (state == 0) {
        return true;
    }

    state_ptr = state;
    
    if (!file_open("console.log", FILE_MODE_WRITE, false, &state_ptr->log_file_handle)) {
        platform_console_write_error("ERROR: Unable to open console.log for writing", LOG_LEVEL_ERROR);
        return false;
    }

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
    czero_memory(out_message, sizeof(out_message));

    __builtin_va_list arg_ptr;
    va_start(arg_ptr, message);
    string_format_v(out_message, message, arg_ptr);
    va_end(arg_ptr);
    
    char p_message[msg_legnth];
    string_format(p_message, "[%s]: %s\n", level_strings[level], out_message);

    // Platform-specific output.
    if (is_error) {
        platform_console_write_error(p_message, level);
    } else {
        platform_console_write(p_message, level);
    }

    append_to_log_file(p_message);
}

