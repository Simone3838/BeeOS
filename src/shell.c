#include <stdint.h>
#include <stddef.h>
#include <string.h>

#define MAX_COMMAND_LENGTH 50
#define MAX_ARGS 5

// Enhanced shell with more commands and features
void shell_init() {
    kernel_print("BeeOS Shell v0.4 \n");
    kernel_print("Type 'help' for available commands\n");
}

// Process information command
void show_processes() {
    kernel_print("Active Processes:\n");
    kernel_print("PID | Status\n");
    kernel_print("---------------\n");
    // In a real implementation, this would reflect actual process states
    kernel_print("0   | Running (Kernel)\n");
    kernel_print("1   | Ready (Shell)\n");
}

// Memory status command
void show_memory_status() {
    kernel_print("Memory Status:\n");
    kernel_print("Total Memory: 1MB\n");
    kernel_print("Free Blocks: 6/8\n");
    kernel_print("Allocated Memory: 128KB\n");
}

void process_command(const char* command) {
    if (command[0] == '\0') return;

    // Enhanced command parsing
    char cmd_buffer[MAX_COMMAND_LENGTH];
    char* args[MAX_ARGS];
    int arg_count = 0;

    // Copy command and parse
    strcpy(cmd_buffer, command);
    char* token = strtok(cmd_buffer, " ");
    
    while (token != 0 && arg_count < MAX_ARGS) {
        args[arg_count++] = token;
        token = strtok(0, " ");
    }

    if (strcmp(args[0], "help") == 0) {
        kernel_print("BeeOS Shell Commands:\n");
        kernel_print("  help      - Show this help menu\n");
        kernel_print("  ver       - Show kernel version\n");
        kernel_print("  ps        - List active processes\n");
        kernel_print("  meminfo   - Display memory information\n");
        kernel_print("  hive      - Hive system status\n");
    } else if (strcmp(args[0], "ver") == 0) {
        kernel_print("BeeOS v0.4 (Enhanced Prototype)\n");
    } else if (strcmp(args[0], "ps") == 0) {
        show_processes();
    } else if (strcmp(args[0], "meminfo") == 0) {
        show_memory_status();
    } else if (strcmp(args[0], "hive") == 0) {
        kernel_print("Hive Status:\n");
        kernel_print("  Workers: 1024 \n");
        kernel_print("  Memory Management: Enabled \n");
        kernel_print("  Process Scheduling: Active \n");
    } else {
        kernel_print("Unknown command: ");
        kernel_print(command);
        kernel_print("\n");
    }
}
