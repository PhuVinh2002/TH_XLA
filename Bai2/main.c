#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Width 256
#define Height 256

void convolution(unsigned char image[Width][Height], int result[Width][Height]) {
    //Gx
    int kernel_x[3][3] = {
        {-1, 0, 1},
        {-2, 0, 2},
        {-1, 0, 1}
    };
    //Gy
    int kernel_y[3][3] = {
        {1, 2, 1},
        {0, 0, 0},
        {-1, -2, -1}
    };

    int result_x[Width][Height];
    int result_y[Width][Height];


    int i, j, m, n;
    int sum;

    // Padding giá trị 0 ở các cạnh 
    unsigned char tempImage[Width + 2][Height + 2];

    for (i = 0; i < Width + 2; ++i) {
        for (j = 0; j < Height + 2; ++j) {
            if (i == 0 || j == 0 || i == Width + 1 || j == Height + 1) {
                tempImage[i][j] = 0; // Thêm giá trị  0
            } else {
                tempImage[i][j] = image[i - 1][j - 1]; // Copy ảnh vào ở giữa
            }
        }
    }

    // Nhân chập với kernel GX
    for (i = 1; i <= Width; ++i) {
        for (j = 1; j <= Height; ++j) {
            sum = 0;
            for (m = -1; m <= 1; ++m) {
                for (n = -1; n <= 1; ++n) {
                    sum += kernel_x[m + 1][n + 1] * tempImage[i + m][j + n];
                }
            }
            result_x[i - 1][j - 1] = sum;
        }
    }
    
    // Nhân chập với kernel Gy
    for (i = 1; i <= Width; ++i) {
        for (j = 1; j <= Height; ++j) {
            sum = 0;
            for (m = -1; m <= 1; ++m) {
                for (n = -1; n <= 1; ++n) {
                    sum += kernel_y[m + 1][n + 1] * tempImage[i + m][j + n];
                }
            }
            result_y[i - 1][j - 1] = sum;
        }
    }

    //Độ lớn độ dốc
    for (i = 1; i <= Width; ++i) {
        for (j = 1; j <= Height; ++j) {
            result[i][j] = sqrt(pow(result_x[i][j], 2) + pow(result_y[i][j], 2));
        }
    }

}

int main() {
    FILE *inputFile = fopen("C:\\Users\\Admin\\Desktop\\Bai2\\grayScale.dat", "rb");
    if (inputFile == NULL) {
        perror("Không thể mở file raw_gray.dat");
        return 1;
    }

    FILE *outputFile = fopen("C:\\Users\\Admin\\Desktop\\Bai2\\edgeImage.dat", "wb");
    if (outputFile == NULL) {
        perror("Không thể mở file raw_edge.dat");
        fclose(inputFile);
        return 1;
    }

    unsigned char image[Width][Height];
    int result[Width][Height];

    // Đọc dữ liệu file ảnh
    fread(image, 1, Width * Height, inputFile);

    // Nhân chập
    convolution(image, result);

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
