#include <stdint.h>
#include <stddef.h>

// Basic VGA text mode buffer
volatile uint16_t* vga_buffer = (volatile uint16_t*)0xB8000;
const int VGA_COLS = 80;
const int VGA_ROWS = 25;

// Color codes
enum VGAColor {
    BLACK = 0,
    BLUE = 1,
    GREEN = 2,
    CYAN = 3,
    RED = 4,
    MAGENTA = 5,
    BROWN = 6,
    GRAY = 7,
    DARK_GRAY = 8,
    BRIGHT_BLUE = 9,
    BRIGHT_GREEN = 10,
    BRIGHT_CYAN = 11,
    BRIGHT_RED = 12,
    BRIGHT_MAGENTA = 13,
    YELLOW = 14,
    WHITE = 15
};

// Create a VGA color code
static inline uint8_t vga_color(enum VGAColor fg, enum VGAColor bg) {
    return fg | bg << 4;
}

// Create a VGA character with color
static inline uint16_t vga_entry(unsigned char c, uint8_t color) {
    return (uint16_t)c | (uint16_t)color << 8;
}

// Clear the screen
void clear_screen() {
    for (int row = 0; row < VGA_ROWS; row++) {
        for (int col = 0; col < VGA_COLS; col++) {
            const size_t index = row * VGA_COLS + col;
            vga_buffer[index] = vga_entry(' ', vga_color(WHITE, BLACK));
        }
    }
}

// Print a string to the screen
void kernel_print(const char* str) {
    static size_t col = 0;
    static size_t row = 0;
    uint8_t color = vga_color(YELLOW, BLACK);

    for (size_t i = 0; str[i] != '\0'; i++) {
        const size_t index = row * VGA_COLS + col;
        
        if (str[i] == '\n') {
            col = 0;
            row++;
            continue;
        }

        vga_buffer[index] = vga_entry(str[i], color);
        col++;

        if (col >= VGA_COLS) {
            col = 0;
            row++;
        }

        if (row >= VGA_ROWS) {
            row = 0;
        }
    }
}

// Enhanced kernel with basic memory management and scheduling
#define KERNEL_VERSION "0.4"
#define MAX_PROCESSES 8
#define MEMORY_SIZE 1024 * 1024  // 1MB of simulated memory

// Process Control Block
typedef struct {
    uint32_t pid;
    enum { READY, RUNNING, BLOCKED, TERMINATED } state;
    uint32_t stack_pointer;
} Process;

// Memory management structures
typedef struct {
    uint8_t* start;
    size_t size;
    uint8_t is_free;
} MemoryBlock;

// Global kernel data structures
static Process processes[MAX_PROCESSES];
static MemoryBlock memory_map[MAX_PROCESSES];
static uint32_t current_pid = 0;

// Memory allocation function
void* kernel_malloc(size_t size) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (memory_map[i].is_free && memory_map[i].size >= size) {
            memory_map[i].is_free = 0;
            return memory_map[i].start;
        }
    }
    return 0;  // Out of memory
}

// Simple process creation
uint32_t create_process(void (*entry)()) {
    for (int i = 0; i < MAX_PROCESSES; i++) {
        if (processes[i].state == TERMINATED) {
            processes[i].pid = i;
            processes[i].state = READY;
            // More advanced process setup would happen here
            return i;
        }
    }
    return (uint32_t)-1;  // Process creation failed
}

// Basic round-robin scheduler
void schedule() {
    current_pid = (current_pid + 1) % MAX_PROCESSES;
    while (processes[current_pid].state != READY) {
        current_pid = (current_pid + 1) % MAX_PROCESSES;
    }
    processes[current_pid].state = RUNNING;
}

void kernel_main() {
    // Initialize memory management
    for (int i = 0; i < MAX_PROCESSES; i++) {
        memory_map[i].start = (uint8_t*)(0x100000 + i * 128 * 1024);  // Start after 1MB
        memory_map[i].size = 128 * 1024;
        memory_map[i].is_free = 1;
        processes[i].state = TERMINATED;
    }

    clear_screen();
    kernel_print("BeeOS Kernel v0.4 Initialized!\n");
    kernel_print("Enhanced with Memory Management \n");
    
    // Demonstrate process and memory capabilities
    kernel_print("Memory Allocation Test: ");
    void* test_memory = kernel_malloc(1024);
    if (test_memory) {
        kernel_print("Successful \n");
    } else {
        kernel_print("Failed, it requires 1024 mb or will won't boot \n");
    }

    // Halt the CPU
    while(1) {}
}
