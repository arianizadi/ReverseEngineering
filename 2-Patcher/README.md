# Binary Patching Tutorial

This tutorial will guide you through the process of analyzing and patching a binary executable. We'll focus on reversing the logic of a conditional jump in an executable using Ghidra, a hex editor, and a custom patcher. The goal is to change a `JNZ` (Jump if Not Zero) instruction to a `JZ` (Jump if Zero) instruction.

---

## Step 1: Analyze the Binary with Ghidra

### Open the Executable
- Launch Ghidra and create a new project.
- Import the target executable (`patchme.exe`) into the project.

### Locate the `if` Statement
- Navigate to the main function (usually `main` or `entry`).
- In the decompiled view, find the logic that verifies the password.

### Identify the `JNZ` Instruction
- Look to the assembly view in Ghidra.
- Locate the `JNZ` (opcode `0x75`) instruction that corresponds to the conditional check.
- Note the file offset of this instruction, by hovering over the address.

![Ghidra View](https://arian-next-blog-assets.s3.us-west-2.amazonaws.com/reverse-engineering/ghidra.png)

---

## Step 2: Verify Offset in a Hex Editor

To ensure you have the correct offset:

- Open the executable in a hex editor.
- Navigate to the offset identified in Ghidra.
- Verify that the byte at this location is `0x75` (the opcode for `JNZ`).

![Hex Editor View](https://arian-next-blog-assets.s3.us-west-2.amazonaws.com/reverse-engineering/hex.png)

---

## Step 3: Patch the Binary

The patching process modifies the byte corresponding to the `JNZ` instruction to `JZ`.

### Key Lines in the Patcher Code

#### 1. Open the Binary File
This ensures the binary file is opened in read-write mode:
```cpp
std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
if (!file.is_open()) {
    std::cerr << "Error: Could not open file!" << std::endl;
    return;
}
```

#### 2. Seek to the Offset
The offset is provided by the user and used to locate the `JNZ` byte:
```cpp
file.seekg(offset, std::ios::beg);
if (!file) {
    std::cerr << "Error: Offset out of range!" << std::endl;
    file.close();
    return;
}
```

#### 3. Validate and Modify the Byte
This reads the byte, checks if it is `0x75`, and changes it to `0x74`:
```cpp
uint8_t byte = 0;
file.read(reinterpret_cast<char*>(&byte), sizeof(byte));
if (byte == 0x75) {
    byte = 0x74;
    file.seekp(offset, std::ios::beg);
    file.write(reinterpret_cast<const char*>(&byte), sizeof(byte));
    std::cout << "Patched successfully!" << std::endl;
} else {
    std::cerr << "Error: Byte is not `JNZ` (0x75)!" << std::endl;
}
```

#### 4. Save and Close the File
After modifying, the file is safely closed:
```cpp
file.close();
```

**Note:** The complete source code for the patcher is available in the project repository.

---

## Step 4: Compile and Run the Patcher

### Makefile
A `Makefile` automates the build process for both the patcher and the executable, I have included one in the project repository.

### Build and Run
1. Use `make` to compile the patcher.
2. Run the patcher and provide the hexadecimal offset of the `JNZ` instruction.

![Patcher Output](https://arian-next-blog-assets.s3.us-west-2.amazonaws.com/reverse-engineering/patcher.png)

---

## Step 5: Test the Patched Binary

- Execute the modified `patchme.exe`.
- Verify that the conditional logic now operates in the reversed manner (e.g., jumps on zero instead of not zero).

---

## Summary

This process demonstrates how to:

1. Use Ghidra to locate critical instructions.
2. Verify offsets with a hex editor.
3. Write a custom patcher to modify binary logic.

Always ensure you have the proper authorization before modifying any software.
