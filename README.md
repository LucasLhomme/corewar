# Corewar — Virtual Machine & Battle Arena

> **Virtual machine and combat arena for concurrent bytecode programs.**

## Overview
The capstone 1st-year Epitech project. Simulates a circular memory space where compiled champion programs (`.cor`) execute concurrently in a shared memory arena:
- Custom instruction set: arithmetic, logical operations, memory jumps, fork processes (`fork`, `lfork`), and alive signals (`live`)
- Process scheduler managing cycle-to-die countdowns and instruction latency
- Memory dumps for state inspection and debugging

## Build & Usage
```bash
make
./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name] ...
```

## License
Open-source under MIT License.
