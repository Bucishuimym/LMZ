#include "bitwriteandreadr.h"
#include "HuffmanTree.h"
#include <string>
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