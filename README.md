# Bare Metal Memory Allocator

## 📜 Overview
This project implements a **custom memory allocator** for a bare-metal system with a fixed 100KB RAM pool.  
It provides `my_alloc()` and `my_free()` functions that mimic dynamic memory allocation without using `malloc` or `free` from the standard C library.  

The allocator:
- Works on a **statically allocated memory pool**.
- Supports block reuse after deallocation.
- Handles allocation requests from **1 byte up to 100 KB**.
- Returns `NULL` if the request cannot be fulfilled.

---

## 🛠 Features
- **Static memory pool** of size 100 KB.
- Metadata table to track allocated blocks.
- Reuses freed blocks to minimize fragmentation.
- Works in **bare metal environments** (no OS required).
- Simple API for integration with any project.

---
