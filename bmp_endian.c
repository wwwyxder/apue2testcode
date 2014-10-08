#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>
#include <string.h>
#pragma pack(2)
struct BMPFILEHEADER
{
    u_int16_t bfType;
    u_int32_t bfSize;
    u_int16_t bfReserved1;
    u_int16_t bfReserved2;
    u_int32_t bfOffBits;
};
struct BMPINFOHEADER
{
    u_int32_t biSize;
    u_int32_t biWidth;
    u_int32_t biHeight;
    u_int16_t biPlanes;
    u_int16_t biBitCount;
    u_int32_t biCompression;
    u_int32_t biSizeImage;
    u_int32_t biXPelsPerMeter;
    u_int32_t biYPelsPerMeter;
    u_int32_t biColorUsed;
    u_int32_t biColorImportant;
};
static void changeEndian(void* src, void* dest, size_t length);

static unsigned long Height;
static unsigned long Width;
static unsigned long BPL;
#define COLOR_R 2
#define COLOR_G 1
#define COLOR_B 0
static void set(int i/*line*/,int j,int COLOR,char v, char* buf)
{
    if(i<0|i>=Height|j<0||j>=Width) return;
    buf[i*BPL+j*3+COLOR] = v;
}
static unsigned char get(int i/*line*/,int j,int COLOR, char* buf)
{
    if(i<0|i>=Height|j<0||j>=Width) return 0;
    return buf[i*BPL+j*3+COLOR];
}
static void setGray(int i,int j,char v,char* buf)
{
    if(i<0|i>=Height|j<0||j>=Width) return;
    buf[i*BPL+j*3+COLOR_B] = v;
    buf[i*BPL+j*3+COLOR_G] = v;
    buf[i*BPL+j*3+COLOR_R] = v;
}
static unsigned char getGray(int i/*line*/,int j, char* buf)
{
    if(i<0|i>=Height|j<0||j>=Width) return 0;
    return (buf[i*BPL+j*3+COLOR_B]+buf[i*BPL+j*3+COLOR_G]+buf[i*BPL+j*3+COLOR_R])/3;
}
static unsigned char getGrayAvg4(int i,int j,char* buf)
{
    unsigned int sum = 0;
    sum += getGray(i-1,j,buf);
    sum += getGray(i+1,j,buf);
    sum += getGray(i,j-1,buf);
    sum += getGray(i,j+1,buf);
    return (unsigned char)(sum/4);
}
int main()
{
    struct BMPFILEHEADER fileHeader;
    struct BMPINFOHEADER infoHeader;
    FILE *fScr = fopen("ThreadsSignals.bmp","rb");
    FILE *fDest = fopen("Dest.bmp","wb");
    if(fread(&fileHeader, sizeof(fileHeader), 1, fScr)!=1) {
        perror("fread fileHeader error");
        return 1;
    }
    if(fread(&infoHeader, sizeof(infoHeader), 1, fScr)!=1) {
        perror("fread info error");
        return 1;
    }
//    changeEndian(&infoHeader.biWidth,&infoHeader.biWidth,sizeof(u_int32_t));
//    changeEndian(&infoHeader.biHeight,&infoHeader.biHeight,sizeof(u_int32_t));
    printf("sizeof(FileHeader):%d\n",sizeof(struct BMPFILEHEADER));
    printf("sizeof(InfoHeader):%d\n",sizeof(struct BMPINFOHEADER));
    Height = infoHeader.biHeight;
    Width = infoHeader.biWidth;
    BPL = (Width*3)+(4-Width*3%4)%4; //Byte per line
    char *buf = malloc(sizeof(char)*Height*BPL);
    fread(buf,1,sizeof(char)*Height*BPL,fScr);
    if(fwrite(&fileHeader, sizeof(fileHeader), 1, fDest)!=1) {
        perror("fwrite fileHeader error");
        return 1;
    }
    if(fwrite(&infoHeader, sizeof(infoHeader), 1, fDest)!=1) {
        perror("fwrite infoHeader error");
        return 1;
    }
    char *wbuf = malloc(sizeof(char)*Height*BPL);
    memcpy(wbuf,buf,sizeof(char)*Height*BPL);
    for(int i=0;i<Height;++i) {
        for(int j=0;j<Width;++j) {
            if(getGray(i,j,buf)<150) {
                setGray(i,j,0,wbuf);
            } else if(getGray(i,j,buf)<=222 && getGrayAvg4(i,j,buf)<getGray(i,j,buf)) {
                setGray(i,j,0,wbuf);
            }
        }
    }
    fwrite(wbuf,1,sizeof(char)*Height*BPL,fDest);
    fclose(fScr);
    fclose(fDest);
    return 0;

}


static void changeEndian(void* src, void* dest, size_t length)
{
    void *p = malloc(length);
    memcpy(p, src, length);
	for(int i=0;i<length;++i) {
		*((char*)dest+i) = *((char*)p+length-1-i);
	}
    free(p);
}
