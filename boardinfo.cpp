#include "boardinfo.h"

boardinfo::boardinfo()
{
    this->writerAddr = 0x00;
    this->readAddr = 0x00;
}

boardinfo::boardinfo(unsigned char addr)
{
    this->writerAddr = addr;
    this->readAddr = addr << 4;
}
