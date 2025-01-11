# LC-3 Virtual Machine (VM) Implementation

This repository contains the implementation of a virtual machine (VM) for the LC-3 architecture based on the tutorial provided in [this blog post](https://www.jmeiners.com/lc3-vm/#:lc3.c_2). The LC-3 is a simple educational processor used in computer science courses to help understand the fundamental concepts of computer architecture.

## Features

- Simulates the LC-3 instruction set and registers.
- Implements memory operations and I/O handling.

## Requirements

- C compiler (e.g., GCC)
- Linux/Unix-like environment (Windows users can use WSL or Cygwin)

## Setup

1. Clone this repository:

   ```bash
   git clone https://github.com/your-repository/lc3-vm.git
   cd lc3-vm
   ```

2. Compile the code:

   ```bash
   make
   ```

3. Run the VM with a program (e.g., `program.obj`):

   ```bash
   ./lc3 program.obj
   ```
  You can try the assembled version of [2048](https://www.jmeiners.com/lc3-vm/supplies/2048.obj) for LC-3 as an example

## Usage

- Load a binary file with LC-3 machine code into the VM.
- The VM will simulate the LC-3's CPU, including registers, memory, and I/O devices.
