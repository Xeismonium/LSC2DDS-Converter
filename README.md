# LSC2DDS Converter

Welcome to the LSC2DDS Converter GitHub repository! This tool is designed to convert LSC (a custom file format from game Lost Saga) to DDS (DirectDraw Surface), a popular format used for storing textures and sprites in video games. The converter is built to be efficient and user-friendly, providing a seamless conversion process.


## Getting Started

### Prerequisites

- C++17 compatible compiler (GCC, Clang, MSVC)

### Installation

1. **Clone the Repository**

```bash
git clone https://github.com/xeismonium/LSC2DDS-Converter.git
cd LSC2DDS-Converter
```

### Usage

Convert a single LSC file to DDS:

```bash
"LSC2DDS Converter.exe" -s [LSC file path] [Output DDS file name]
```

Convert all LSC files in a directory:

```bash
"LSC2DDS Converter.exe" -d [Directory containing LSC files]
```

### Examples

- Converting a single file:

```bash
"LSC2DDS Converter.exe" -s example.lsc example.dds
```

- Converting multiple files in a directory:

```bash
"LSC2DDS Converter.exe" -d ./lsc_files
```

### Original Source
https://github.com/ccdbgt/lsc2dds
