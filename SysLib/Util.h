
#ifndef  _UTIL_H_
#define  _UTIL_H_

WORD Util_u16ByteSwap(WORD u16Word);
DWORD Util_u16DWORDSwap(DWORD u32Word);

SHORT Util_u8String2int16(char* Data);

DWORD Util_u8String2DWORD(char* Data);

//limted to 1 digit fraction value eg 5.3.
float Util_u8String2Float(char* Data);
float Util_u8String2NFloat(char* Data);

#endif
