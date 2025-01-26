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

LICENSE.md
