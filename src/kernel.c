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

void kernel_main() {
    // Initialize the kernel
    clear_screen();
    kernel_print("BeeOS Kernel Initialized!\n");
    kernel_print("Welcome to the hive!\n");

    // Halt the CPU
    while(1) {}
}
