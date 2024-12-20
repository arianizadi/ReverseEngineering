#include <cstdint>
#include <fstream>
#include <iostream>
#include <string>

// Patch binary function
void patchBinary(const std::string& filePath, std::streamoff offset) {
  // Open the file in binary read-write mode
  std::fstream file(filePath, std::ios::in | std::ios::out | std::ios::binary);
  if(!file.is_open()) {
    std::cerr << "Error: Could not open file!" << std::endl;
    return;
  }

  // Seek to the calculated offset
  file.seekg(offset, std::ios::beg);
  if(!file) {
    std::cerr << "Error: Offset out of range!" << std::endl;
    file.close();
    return;
  }

  // Read the byte at the calculated offset
  uint8_t byte = 0;
  file.read(reinterpret_cast< char* >(&byte), sizeof(byte));
  if(!file) {
    std::cerr << "Error: Failed to read from file!" << std::endl;
    file.close();
    return;
  }

  // Check if the byte corresponds to `JNZ` (0x75)
  if(byte == 0x75) {
    // Replace `JNZ` with `JZ` (0x74)
    byte = 0x74;
    file.seekp(offset, std::ios::beg);
    file.write(reinterpret_cast< const char* >(&byte), sizeof(byte));
    if(file) {
      std::cout << "Patched successfully!" << std::endl;
    } else {
      std::cerr << "Error: Failed to write to file!" << std::endl;
    }
  } else {
    std::cerr << "Error: Byte at offset is not `JNZ` (0x75)!" << std::endl;
  }

  // Close the file
  file.close();
}

int main() {
  std::string filePath = "patchme.exe";
  std::streamoff offset;

  std::cout << "Enter the offset (in hexadecimal): ";
  std::cin >> std::hex >> offset;

  patchBinary(filePath, offset);

  return 0;
}
