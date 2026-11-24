#include <cstdint>
#include <fstream>
#include <string>
#include <vector>

#include "filewr.h"

bool FileWR::readFile(const std::string& path, std::vector<std::uint8_t>& out)
{
    std::ifstream in(path, std::ios::binary);
    if (!in) {
        return false;
    }

    out.clear();
    char buf[64 * 1024];
    while (in.read(buf, sizeof buf) || in.gcount() > 0) {
        const auto* p = reinterpret_cast<const std::uint8_t*>(buf);
        out.insert(out.end(), p, p + in.gcount());
    }

    return !in.bad();
}

bool FileWR::writeFile(const std::string& path,const std::vector<std::uint8_t>& data)
{
    std::ofstream out(path, std::ios::binary | std::ios::trunc);
    if (!out) {
        return false;
    }

    out.write(reinterpret_cast<const char*>(data.data()),
              static_cast<std::streamsize>(data.size()));
    out.flush();

    return static_cast<bool>(out);
}