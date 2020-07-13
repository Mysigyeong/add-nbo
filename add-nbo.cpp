#include <cstdint>
#include <cstdio>
#include <netinet/in.h>

using namespace std;

int main(int argc, char* argv[])
{
    FILE* fp1 = NULL;
    FILE* fp2 = NULL;
    
    if (argc != 3) {
        printf("Usage: %s <file1> <file2>\n", argv[0]);
        return 1;
    }

    try {
        fp1 = fopen(argv[1], "r");
        fp2 = fopen(argv[2], "r");
        if (!fp1 || !fp2) throw 1;
    }
    catch(int n) {
        puts("File open failed");
        if (!fp1) fclose(fp1);
        if (!fp2) fclose(fp2);
        return 1;
    }

    uint32_t val1;
    uint32_t val2;
    uint32_t result;

    try {
        int num1 = fread(&val1, sizeof(uint32_t), 1, fp1);
        int num2 = fread(&val2, sizeof(uint32_t), 1, fp2);
        
        if (num1 < 0 || num2 < 0) throw 1;
    }
    catch(int n) {
        puts("fread failed");
        fclose(fp1);
        fclose(fp2);
        return 1;
    }

    val1 = ntohl(val1);
    val2 = ntohl(val2);
    result = val1 + val2;
    printf("%d(0x%x) + %d(0x%x) = %d(0x%x)\n", val1, val1, val2, val2, result, result);

    fclose(fp1);
    fclose(fp2);
    return 0;
}