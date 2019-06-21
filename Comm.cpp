#include <string>
#include <windows.h>

using namespace std;

int String2Hex(string &str, BYTE *pOut, DWORD *pLenOut, DWORD nMaxLen) {
    int i, j = 0;
    DWORD len;
    TCHAR x;
    for (i = 0, x = 0, len = 0;
         i < (int) str.length() && len < (int) nMaxLen;
         i++) {
        if (j >= 2) {
            pOut[len++] = (BYTE) x;
            x = 0;
            j = 0;
        }
        if (str[i] >= '0' && str[i] <= '9') {
            x <<= 4;
            x |= str[i] - '0';
            j++;
        } else if ((str[i] >= 'A' && str[i] <= 'F')
                   || (str[i] >= 'a' && str[i] <= 'f')) {
            x <<= 4;
            x |= _toupper (str[i]) - 'A' + 10;
            j++;
        } else if (j) {
            pOut[len++] = (BYTE) x;
            x = 0;
            j = 0;
        }

    }
    if (j) {
        pOut[len++] = (BYTE) x;
        x = 0;
        j = 0;
    }

    if (pLenOut)
        *pLenOut = len;

    return 0;
}

string StringAddSpace(string &input) {
    string output = "";
    for (int i = 0; i < input.length(); i += 2) {
        output = output + input[i] + input[i + 1] + ' ';
    }
    return output;
}
