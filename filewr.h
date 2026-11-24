#ifndef FILEWR_H
#define FILEWR_H

#include <string>
#include <vector>
#include <cstdint>
class FileWR
{
private:
    const std::string path = "";
public:
    FileWR();
    ~FileWR() = delete;
    bool readFile(const std::string& PATH,std::vector<uint8_t>& out);
    bool writeFile(const std::string& PATH,const std::vector<uint8_t>& data);
};

#endif // FILEWR_H
