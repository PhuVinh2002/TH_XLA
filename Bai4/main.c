#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define Width 256
#define Height 256
#define Parts 64

void maxtrixDivision(unsigned char image[Width][Height], unsigned char result[]){
        int partRows = Width / Parts;
        int partCols = Height / Parts;
    for (int i = 0; i < Parts; ++i) {
        for (int j = 0; j < Parts; ++j) {
            int sum = 0;
            for (int row = i * partRows; row < (i + 1) * partRows; ++row) {
                for (int col = j * partCols; col < (j + 1) * partCols; ++col) {
                    sum += image[row][col];
                }
            }
            result[i * Parts + j] = sum;
        }
    }
}

int Max(int a, int b, int c, int d){
        int max = a;

        if (b > max) {
            max = b;
        }
        if (c > max) {
            max = c;
        }
        if (d > max) {
            max = d;
        }
        return max;
}
void convertEdge(const char *diagonalDown, const char *diagonalUp, const char *horizotal, const char *vertical,
const char *outputDiagonalDown, const char *outputDiagonalUp, const char *outputHorizotal, const char *ouputVertical) {
    
    FILE *inputFileDiagonalDown = fopen(diagonalDown, "rb");
    FILE *inputFileDiagonalUp = fopen(diagonalUp, "rb");
    FILE *inputFileHorizontal = fopen(horizotal, "rb");
    FILE *inputFileVertical = fopen(vertical, "rb");

    FILE *outputFileDiagonalDown = fopen(outputDiagonalDown, "wb");
    FILE *outputFileDiagonalUp = fopen(outputDiagonalUp, "wb");
    FILE *outputFileHorizontal = fopen(outputHorizotal, "wb");
    FILE *outputFileVertical = fopen(ouputVertical, "wb");

    unsigned char imageDiagonalDown[Width][Height];
    unsigned char imageDiagonalUp[Width][Height];
    unsigned char imageHorizontal[Width][Height];
    unsigned char imageVertical[Width][Height];
    
    fread(imageDiagonalDown, 1, Width * Height, inputFileDiagonalDown);
    fread(imageDiagonalUp, 1, Width * Height, inputFileDiagonalUp);
    fread(imageHorizontal, 1, Width * Height, inputFileHorizontal);
    fread(imageVertical, 1, Width * Height, inputFileVertical);

    unsigned char winnerTakeAll;
    unsigned char zero = 0;
    unsigned char one = 1;
        for (int i = 0; i < Width; ++i) {
            for (int j = 0; j < Height; ++j) {
                winnerTakeAll = Max(abs(imageDiagonalDown[i][j]),abs(imageDiagonalUp[i][j]),abs(imageHorizontal[i][j]),abs(imageVertical[i][j]));
                if(winnerTakeAll == abs(imageDiagonalDown[i][j])){
                    if(winnerTakeAll > 127){
                        fwrite(&one, 1, 1, outputFileDiagonalDown);
                        fwrite(&zero, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileVertical);
                    }
                    else{
                        fwrite(&zero, 1, 1, outputFileDiagonalDown);
                        fwrite(&zero, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileVertical);
                    }
                }
                else if(winnerTakeAll == abs(imageDiagonalUp[i][j])){
                    if(winnerTakeAll > 127){
                        fwrite(&one, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileDiagonalDown);
                        fwrite(&zero, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileVertical);
                    }
                    else{
                        fwrite(&zero, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileDiagonalDown);
                        fwrite(&zero, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileVertical);
                    }
                }
                else if(winnerTakeAll == abs(imageHorizontal[i][j])){
                    if(winnerTakeAll > 127){
                        fwrite(&one, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileDiagonalDown);
                        fwrite(&zero, 1, 1, outputFileVertical);
                    }
                    else{
                        fwrite(&zero, 1, 1, outputFileDiagonalDown);
                        fwrite(&zero, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileVertical);
                    }
                }
                else if(winnerTakeAll == abs(imageVertical[i][j])){
                    if(winnerTakeAll > 127){
                        fwrite(&one, 1, 1, outputFileVertical);
                        fwrite(&zero, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileDiagonalDown);
                    }
                    else{
                        fwrite(&zero, 1, 1, outputFileDiagonalDown);
                        fwrite(&zero, 1, 1, outputFileDiagonalUp);
                        fwrite(&zero, 1, 1, outputFileHorizontal);
                        fwrite(&zero, 1, 1, outputFileVertical);
                    }
                }
            }
        }
        fclose(inputFileDiagonalDown);
        fclose(inputFileDiagonalUp);
        fclose(inputFileHorizontal);
        fclose(inputFileVertical);

        fclose(outputFileDiagonalDown);
        fclose(outputFileDiagonalUp);
        fclose(outputFileHorizontal);
        fclose(outputFileVertical);
}

void sumVetor(const char *diagonalDown, const char *diagonalUp, const char *horizotal, const char *vertical,const char *output_path) {

    FILE *FileDiagonalDown = fopen(diagonalDown, "rb");
    FILE *FileDiagonalUp = fopen(diagonalUp, "rb");
    FILE *FileHorizontal = fopen(horizotal, "rb");
    FILE *FileVertical = fopen(vertical, "rb");

    unsigned char DiagonalDown[Width][Height];
    unsigned char DiagonalUp[Width][Height];
    unsigned char Horizontal[Width][Height];
    unsigned char Vertical[Width][Height];
    
    fread(DiagonalDown, 1, Width * Height, FileDiagonalDown);
    fread(DiagonalUp, 1, Width * Height, FileDiagonalUp);
    fread(Horizontal, 1, Width * Height, FileHorizontal);
    fread(Vertical, 1, Width * Height, FileVertical);

    // Chia ma trận thành 64 phần và tính tổng từng phần

    unsigned char VectorDiagonalDown[] = {0};
    unsigned char VectorDiagonalUp[] = {0};
    unsigned char VectorHorizontal[] = {0};
    unsigned char VectorVertical[] = {0};
    unsigned char Vecto[256];

    maxtrixDivision(DiagonalDown,VectorDiagonalDown);
    maxtrixDivision(DiagonalUp,VectorDiagonalUp);
    maxtrixDivision(Horizontal,VectorHorizontal);
    maxtrixDivision(Vertical,VectorVertical);

    // Chuyển lần lượt giá trị của 4 mảng sang mảng duy nhất
    int currentIndex = 0;  

    for (int i = 0; i < Parts; ++i) {
            Vecto[currentIndex++] = VectorDiagonalDown[i];
    }
    for (int i = 0; i < Parts; ++i) {
            Vecto[currentIndex++] = VectorDiagonalUp[i];
            
    }
    for (int i = 0; i < Parts; ++i) {
            Vecto[currentIndex++] = VectorHorizontal[i];
    }
    for (int i = 0; i < Parts; ++i) {
            Vecto[currentIndex++] = VectorVertical[i];
    }

    FILE *outputFileVector = fopen(output_path, "wb");

    for (int i = 0; i < Parts*Parts; ++i) {
            unsigned char value = Vecto[i];
            fwrite(&value, 1, 1, outputFileVector);
    }
    fclose(outputFileVector);
    fclose(FileDiagonalDown);
    fclose(FileDiagonalUp);
    fclose(FileHorizontal);
    fclose(FileVertical);
}

void calculateDistance(const char *output_path1, const char *output_path2) {

    FILE *inputFileVector1 = fopen(output_path1, "rb");
    FILE *inputFileVector2 = fopen(output_path2, "rb");

    
    unsigned char result1[Width];
    unsigned char result2[Width];

    fread(result1, 1, Width, inputFileVector1);
    fread(result2, 1, Width, inputFileVector2);

    double distance = 0.0;
    for (int i = 0; i < Width; ++i) {
        distance += pow(result2[i] - result1[i], 2);
    }

    distance = sqrt(distance);

    printf("Khoang cach giua hai mang la: %f\n", distance);
    
}
int main(){
    
    convertEdge("C:\\Users\\Admin\\Desktop\\Bai4\\raw_DiagonalDown1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\raw_DiagonalUp1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\raw_Horizotal1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\raw_Vertical1.dat",
                "C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalDown1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalUp1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputHorizotal1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputVertical1.dat");
    convertEdge("C:\\Users\\Admin\\Desktop\\Bai4\\raw_DiagonalDown.dat","C:\\Users\\Admin\\Desktop\\Bai4\\raw_DiagonalUp.dat","C:\\Users\\Admin\\Desktop\\Bai4\\raw_Horizotal.dat","C:\\Users\\Admin\\Desktop\\Bai4\\raw_Vertical.dat",
                "C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalDown.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalUp.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputHorizotal.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputVertical.dat");
    sumVetor("C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalDown1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalUp1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputHorizotal1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputVertical1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\vector1.dat");
    sumVetor("C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalDown.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalUp.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputHorizotal.dat","C:\\Users\\Admin\\Desktop\\Bai4\\outputVertical.dat","C:\\Users\\Admin\\Desktop\\Bai4\\vector.dat");
    calculateDistance("C:\\Users\\Admin\\Desktop\\Bai4\\vector1.dat","C:\\Users\\Admin\\Desktop\\Bai4\\vector.dat");


    

    
}


