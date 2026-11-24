#include "bitwriteandreadr.h"
#include "HuffmanTree.h"
#include <vector>

using namespace huftre;
using namespace std;

void BitWriter::writeBit(int bit){
    buf = static_cast<Byte>((buf<<1)|(bit&1));
    if(++cnt == 8){
        out.push_back(buf);
        buf = 0;
        cnt = 0;
    }
}

void BitWriter::flush(){
    if(cnt > 0){
        buf <<= (8 - cnt);
        out.push_back(buf);
        buf = 0;
        cnt = 0;
    }
}

static void writeU32(vector<Byte>& v,uint32_t x){
    v.push_back(x & 0xFF);
    v.push_back(x >> 8);
    v.push_back(x >> 16);
    v.push_back(x >> 24);
}
static void writeU64(vector<Byte>& v,Count x){
    for(int i = 0; i < 8; ++i){
        v.push_back((x >> (8*i)) & 0xFF);
    }
}
static void readU32(const std::vector<Byte>& v,size_t& pos){
    uint32_t x =0;
    for(int i=0;i<4;++i){
        x |= uint32_t(v[pos++]) << (8*i);
    }
    return;
}
static void readU64(const std::vector<Byte>& v,size_t& pos){
    Count x = 0;
    for(int i=0;i<8;++i){
        x |= Count(v[pos++]) << (8*i);
    }
    return;
}