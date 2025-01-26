# BeeOS

BeeOS is a custom, hobby operating system developed from scratch, focusing on simplicity, modularity, and learning the intricacies of low-level system programming.

## Project Goals

- Learn operating system development
- Create a lightweight, modular kernel
- Implement basic system services
- Explore low-level programming techniques

## Build Requirements

- gcc
- nasm
- ld
- grub-mkrescue
- qemu (for testing)

## Building

1. Ensure all build dependencies are installed
2. Run `make iso` to create the bootable ISO
3. Run `make run` to test in QEMU

## Current Features

- 32-bit protected mode kernel
- Basic VGA text output
- Simple shell with built-in commands

## Roadmap

- [ ] Memory management
- [ ] Interrupt handling
- [ ] Process scheduling
- [ ] File system support

## Inspiration

Inspired by the collaborative and industrious nature of bees, BeeOS aims to be a learning project that builds complexity through simple, well-structured components.

## License
MIT License

Copyright (c) 2025 Simone3838

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
