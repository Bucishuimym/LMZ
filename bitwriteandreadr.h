#ifndef BITWRITEANDREADR_H
#define BITWRITEANDREADR_H

#include <vector>
#include "HuffmanTree.h"

class BitWriter
{
private:
    std::vector<huftre::Byte>& out;
    huftre::Byte buf = 0;
    int cnt = 0;
public:
    explicit BitWriter(std::vector<huftre::Byte>& _out):out(_out){}
    void writeBit(int bit);
    void flush();
};

class BitReader{
private:
    const std::vector<huftre::Byte>& in;
    size_t bitPos = 0;
public:
    explicit BitReader(std::vector<huftre::Byte>& _in):in(_in){}
    void readerBit(int& bit);
};

#endif // BITWRITEANDREADR_H
