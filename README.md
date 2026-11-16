# ⚔️ Corewar — Virtual Machine & Bytecode Battle Arena in C

[![Language: C](https://img.shields.io/badge/Language-C-00599C.svg)](https://en.wikipedia.org/wiki/C_(programming_language))
[![Build: Make](https://img.shields.io/badge/Build-Makefile-orange.svg)](Makefile)
[![Module: B-CPE-200](https://img.shields.io/badge/Epitech-B--CPE--200-blue.svg)](https://www.epitech.eu/)
[![License: MIT](https://img.shields.io/badge/License-MIT-green.svg)](LICENSE)
[![Academic Year: 2024-2025](https://img.shields.io/badge/Academic%20Year-2024--2025%20(Tek1)-blueviolet.svg)](#)

> **Corewar is the premier first-year capstone project at Epitech.** It is a virtual computer simulation where compiled bytecode champion programs fight for dominance in a circular memory arena.

---

## 🎯 Game Concept

In Corewar, 2 to 4 champion programs (`.cor` binary files) are loaded into a shared circular memory arena of **6144 bytes (`MEM_SIZE`)**.
- Champions execute low-level assembly bytecode instructions concurrently.
- The goal is to survive by executing the `live` instruction and overwriting competitor memory instructions with traps, illegal opcodes, or forks.
- A countdown timer (`CYCLE_TO_DIE = 1536`) periodically decreases. Champions that fail to signal `live` during the period are eliminated.

---

## ⚙️ Virtual Machine Specifications

### 1. Circular Memory Arena
- Total Memory: **6144 bytes (`MEM_SIZE`)**.
- Addressing: Circular memory wrapping using `idx_mod = 512` (`IDX_MOD`). Jumps and indirect addressing cannot write outside relative bounds.

### 2. Process Registers & Architecture
Each running process possesses:
- **PC (Program Counter):** Address pointer within the circular arena.
- **Carry Flag:** Boolean flag set by arithmetic and logical operations (`add`, `sub`, `and`, `or`, `xor`).
- **Registers:** 16 general-purpose registers (`r1` to `r16`), each 4 bytes wide.
- **Cycle Latency:** Instructions require between 2 and 1000 execution cycles before committing state changes.

### 3. Instruction Set (16 Opcodes)
| Opcode | Mnemonic | Cycles | Description |
| :---: | :--- | :---: | :--- |
| `0x01` | `live` | 10 | Declares the player alive; resets cycle-to-die validation. |
| `0x02` | `ld` | 5 | Loads a value from memory into a register. |
| `0x03` | `st` | 5 | Stores a register value into memory or another register. |
| `0x04` | `add` | 10 | Adds two registers and writes result into third register; sets carry. |
| `0x05` | `sub` | 10 | Subtracts two registers; sets carry. |
| `0x06` | `and` | 6 | Bitwise AND on two operands; sets carry. |
| `0x07` | `or` | 6 | Bitwise OR on two operands; sets carry. |
| `0x08` | `xor` | 6 | Bitwise XOR on two operands; sets carry. |
| `0x09` | `zjmp` | 20 | Jumps to target PC address if carry flag is 1. |
| `0x0a` | `ldi` | 25 | Loads index from memory using address offset addition. |
| `0x0b` | `sti` | 25 | Stores index into memory using address offset addition. |
| `0x0c` | `fork` | 800 | Spawns a clone child process inheriting registers and state. |
| `0x0d` | `lld` | 10 | Long load without `IDX_MOD` boundary restrictions. |
| `0x0e` | `lldi` | 50 | Long load index without `IDX_MOD` boundary restrictions. |
| `0x0f` | `lfork` | 1000 | Spawns child process without `IDX_MOD` jump restriction. |
| `0x10` | `aff` | 2 | Displays character specified by register value (modulo 256). |

---

## 🛠️ Build & Usage

```bash
make
./corewar [-dump nbr_cycle] [[-n prog_number] [-a load_address] prog_name.cor] ...
```

### Options:
- `-dump nbr_cycle`: Dumps memory state to stdout at the specified cycle number and exits.
- `-n prog_number`: Assigns an explicit champion number.
- `-a load_address`: Fixes the initial loading memory offset.

---

## 📜 License

Licensed under the **MIT License with attribution** to Lucas Lhomme (Crabe).
