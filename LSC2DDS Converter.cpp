#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>

namespace fs = std::filesystem;

std::vector<uint8_t> transformBytes(const std::vector<uint8_t>& data) {
    std::vector<uint8_t> transformedData = data;
    for (auto& byte : transformedData) {
        uint8_t temp = (byte & 0x7) << 5;
        byte >>= 3;
        byte |= temp;
        byte ^= 0xff;
    }
    return transformedData;
}

void processDirectory(const fs::path& dirPath) {
    for (const auto& entry : fs::directory_iterator(dirPath)) {
        if (entry.path().extension() == ".lsc") {
            std::ifstream inFile(entry.path(), std::ios::binary);
            std::vector<uint8_t> data((std::istreambuf_iterator<char>(inFile)),
                std::istreambuf_iterator<char>());
            inFile.close();

            auto transformedData = transformBytes(data);

            fs::path outputFilepath = entry.path(); 
            outputFilepath.replace_extension(".dds");

            std::ofstream outFile(outputFilepath, std::ios::binary);
            outFile.write(reinterpret_cast<const char*>(transformedData.data()), transformedData.size());
            outFile.close();

            std::cout << "Written File : " << outputFilepath << std::endl;
        }
    }
}


void processSingleFile(const fs::path& filePath, const std::string& nextName) {
    std::ifstream inFile(filePath, std::ios::binary);
    std::vector<uint8_t> data((std::istreambuf_iterator<char>(inFile)),
        std::istreambuf_iterator<char>());
    inFile.close();

    auto transformedData = transformBytes(data);

    fs::path outFilepath = filePath.parent_path() / (nextName.find(".dds") != std::string::npos ? nextName : nextName + ".dds");
    std::ofstream outFile(outFilepath, std::ios::binary);
    outFile.write(reinterpret_cast<const char*>(transformedData.data()), transformedData.size());
    outFile.close();

    std::cout << "Written File : " << outFilepath << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc < 3) {
        std::cout << "Please fill Dir args and Prefix args" << std::endl;
        return 1;
    }

    std::string pref = argv[1];
    fs::path dirPath = argv[2];

    if (pref == "-d") {
        processDirectory(dirPath);
    }
    else if (pref == "-s") {
        if (argc < 4) {
            std::cout << "Please fill after named args" << std::endl;
            return 1;
        }
        std::string nextName = argv[3];
        processSingleFile(dirPath, nextName);
    }
    else {
        std::cout << "Invalid prefix command!" << std::endl;
    }

    return 0;
}
