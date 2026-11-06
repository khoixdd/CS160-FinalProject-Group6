#include "Storage.h"

#include <fstream>
#include <cstdint>
// INCOMPLETE SCAFFOLD. Implement the assigned public functions and tests.
// See ../MANAGEMENT/WEEKLY_PLAN.md in the local team workspace.

bool writeRaw(std::ostream& output, const char* data, std::streamsize byteCount) {
    if (byteCount < 0) {
        return false;
    }
    if (byteCount == 0) {
        return static_cast<bool>(output);
    }
    output.write(data, byteCount);
    return static_cast<bool>(output);
}

bool readRaw(std::istream& input, char* data, std::streamsize byteCount) {
    if (byteCount < 0) {
        return false;
    }
    if (byteCount == 0) {
        return static_cast<bool>(input);
    }
    input.read(data, byteCount);
    return input.gcount() == byteCount && static_cast<bool>(input);
}

bool writeInt32(std::ostream& output, std::int32_t value) {
    return writeRaw(output, reinterpret_cast<const char*>(&value), sizeof(value));
}

bool readInt32(std::istream& input, std::int32_t& value) {
    return readRaw(input, reinterpret_cast<char*>(&value), sizeof(value));
}

bool writeUInt32(std::ostream& output, std::uint32_t value) {
    return writeRaw(output, reinterpret_cast<const char*>(&value), sizeof(value));
}

bool readUInt32(std::istream& input, std::uint32_t& value) {
    return readRaw(input, reinterpret_cast<char*>(&value), sizeof(value));
}

bool writeInt64(std::ostream& output, std::int64_t value) {
    return writeRaw(output, reinterpret_cast<const char*>(&value), sizeof(value));
}

bool readInt64(std::istream& input, std::int64_t& value) {
    return readRaw(input, reinterpret_cast<char*>(&value), sizeof(value));
}