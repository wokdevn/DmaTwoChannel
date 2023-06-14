#include <stdio.h>
#include <stdlib.h>
#include "../head/interdma.h"
#include "../head/utilMM2S.h"

//modu:11, mb:9, ldpcnum:15
//bin: 0001 0000, 0010 0000, 0011 0000, 0100 0000, 0101 "11""00, 1001" "0000, 0111 1"000, 1000 0000,
//#define TEST_DATA 0x102030405"8"607080
#define TEST_DATA 0x102030405c907880

// crc:false, ldpc_ok:19, amp:2,  modu:11, mb:9, ldpcnum:15
//bin: 0001 0000, 0010 0000, 0011 0000, "0""000 0100, 11"11" "11""00, 1000" "0000, 0110 0"000, 1000 0000,
//#define TEST_DATA 0x102030405"8"607080
#define TEST_DATA_S2MM 0x01203004fc806880

#define CHANNEL_CORRECT_GROUP 69
#define DATA_EQU_BLOCK 10
#define MODU_CHARACTOR 448
#define DATA_MAX MODU_CHARACTOR*(CHANNEL_CORRECT_GROUP*DATA_EQU_BLOCK-1)
#define HOLE 512
#define DATA_TR(mb) ((mb+22)*256-HOLE)
#define LDPC_K 5632

int main() {
    printf("Hello, World!\n");
    long data = TEST_DATA;
    printf("data: 0x%lx\n",data);
    print_b(&data,sizeof(data));

    unsigned char charpack[8] = {0};
    long2char(data,charpack);

    unsigned char bitpack[64] = {0};
    char2bit(charpack,8,bitpack);

    mm2s_f mf;
    getParamM2S(&mf,bitpack);

    int i = getHeadM2S(charpack);
    printf("head:%d\n",i);
    printf("modu:%d\n",mf.modulation);
    printf("mb:%d\n",mf.Mb);
    printf("ldpc num:%d\n",mf.ldpcNum);

    int mod_p = 0;
    switch (mf.modulation){
        case BPSK:
            mod_p = 1;
            break;
        case QPSK:
            mod_p = 2;
        case QAM16:
            mod_p = 4;
        case QAM64:
            mod_p = 6;
    }

    long data_s = TEST_DATA_S2MM;
    printf("data_S: 0x%lx\n",data_s);
    print_b(&data_s,sizeof(data_s));

    unsigned char charpack_s[8] = {0};
    long2char(data_s,charpack_s);

    unsigned char bitpack_s[64] = {0};
    char2bit(charpack_s,8,bitpack_s);

    s2mm_f sf;
    getParamS2M(&sf,bitpack_s);

    int j = getHeadS2M(charpack_s);
    printf("head:%d\n",j);
    printf("crc:%d\n",sf.crc_r);
    printf("ldpc_t:%d\n",sf.ldpc_tnum);
    printf("amp:%d\n",sf.amp_dresult);
    printf("modula:%d\n",sf.modu);
    printf("mb:%d\n",sf.Mb);
    printf("ldpcnum:%d\n",sf.ldpcnum);


    mm2s_f msf;
    msf.ldpcNum = 21;
    msf.Mb = 11;
    msf.modulation = QPSK;
    unsigned char pack[8] = {0};
    constrM2S(&msf,&pack);

    unsigned char bitpack_c[64] = {0};
    char2bit(pack,8,bitpack_c);
    for(int i = 0;i<64;++i){
        printf("%c",bitpack_c[i]+'0');
    }
    printf("\n");

    mm2s_f mf_c;
    getParamM2S(&mf_c,bitpack_c);

    int i_c = getHeadM2S(pack);
    printf("head:%d\n",i_c);
    printf("modu:%d\n",mf_c.modulation);
    printf("mb:%d\n",mf_c.Mb);
    printf("ldpc num:%d\n",mf_c.ldpcNum);

//    getParamM2S(&mf,pack);
//
//    int ii = getHeadM2S(pack);
//    printf("head:%d\n",ii);
//    printf("modu:%d\n",mf.modulation);
//    printf("mb:%d\n",mf.Mb);
//    printf("ldpc num:%d\n",mf.ldpcNum);

//    unsigned char test[8] = {'0','1','1','1','0','0','0','1'};
//    unsigned char testa = 0;
//    bit2char(test,1,&testa);
//    printf("0x%x",testa);

    return 0;
}
