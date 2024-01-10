#include <stdio.h>
#include <stdlib.h>
#include "convolutionAlgorithm.h"

#define Width 256
#define Height 256

int main() {
    int kernel[3][3] = {
        {0, -1, -2},
        {1, 0, -1},
        {2, 1, 0}
    };
    FILE *inputFile = fopen("C:\\Users\\Admin\\Desktop\\Bai4\\raw_gray.dat", "rb");
    if (inputFile == NULL) {
        perror("Không thể mở file raw_gray.dat");
        return 1;
    }

    FILE *outputFile = fopen("C:\\Users\\Admin\\Desktop\\Bai4\\raw_DiagonalDown.dat", "wb");
    if (outputFile == NULL) {
        perror("Không thể mở file raw_DiagonalDown.dat");
        fclose(inputFile);
        return 1;
    }


    unsigned char image[Width][Height];
    int result[Width][Height];


    // Đọc dữ liệu file ảnh
    fread(image, 1, Width * Height, inputFile);

    // Nhân chập
    convolution(image,kernel,result);
    
    // Ghi giá trị kết quả nhân chập ra file
    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Height; ++j) {
            unsigned char value = result[i][j];
            fwrite(&value, 1, 1, outputFile);
        }
    }
    fclose(inputFile);
    fclose(outputFile);

    return 0;
}
