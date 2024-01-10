#include <stdio.h>
#include <stdlib.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  

void readImage(const char* image_path, const char* output_path) {

    int width, height, channels;

    // Đọc ảnh từ file
    unsigned char *image = stbi_load(image_path, &width, &height, &channels, STBI_rgb);

    if (image == NULL) {
        fprintf(stderr, "Không thể đọc ảnh\n");
        return;
    }
    
    // Mở file để lưu giá trị pixel
    FILE *file = fopen(output_path, "wb");
    if (file == NULL) {
        fprintf(stderr, "Không thể mở file để ghi\n");
        stbi_image_free(image);
        return;
    }
    // Ghi kích thước ảnh vào file
    fwrite(&width, sizeof(int), 1, file);
    fwrite(&height, sizeof(int), 1, file);

    // Ghi giá trị từng pixel vào file
    for (int i = 0; i < width * height * channels; ++i) {
        fwrite(&image[i], sizeof(unsigned char), 1, file);
    }

    // Đóng file và giải phóng bộ nhớ
    fclose(file);
    stbi_image_free(image);

    printf("Save Sucessfull\n");
}
void convertToGrayscale(const char* image_path, const char* output_path) {

    FILE *inputFile = fopen(image_path, "rb");
    if (inputFile == NULL){
        perror("Không thể mở file .dat");
        return;
    }
    FILE *outputFile = fopen(output_path, "wb");
    if (outputFile == NULL){
        perror("Không thể mở file gray.dat");
        fclose(inputFile);
        return;
    }
    while (1) {
        unsigned char pixel[3];
        size_t bytesRead = fread(pixel, 1, 3, inputFile); 

        if (bytesRead < 3){
            if (feof(inputFile)){
                break; // Đã đọc hết file
            } else{
                perror("Lỗi khi đọc file raw.dat");
                fclose(inputFile);
                fclose(outputFile);
                return;
            }
        }
        unsigned char gray = (pixel[0] + pixel[1] + pixel[2])/3;
        // Ghi dữ liệu grayscale vào file raw_gray.dat
        fwrite(&gray, 1, 1, outputFile);
    }
    // Đóng các file
    fclose(inputFile);
    fclose(outputFile);
}
void convertToBinary(const char* image_path, const char* output_path) {

    FILE *inputFile = fopen(image_path, "rb");
    if (inputFile == NULL){
        perror("Không thể mở file .dat");
        return;
    }
    FILE *outputFile = fopen(output_path, "wb");
    if (outputFile == NULL){
        perror("Không thể mở file gray.dat");
        fclose(inputFile);
        return;
    }
    while (1) {
        unsigned char pixel[1];
        size_t bytesRead = fread(pixel, 1, 1, inputFile);

        if (bytesRead < 1){
            if (feof(inputFile)){
                break; // Đã đọc hết file
            } else{
                perror("Lỗi khi đọc file raw.dat");
                fclose(inputFile);
                fclose(outputFile);
                return;
            }
        }
        unsigned char gray;
        if (pixel[0] > 127) gray = 1;
        else gray = 0;
        fwrite(&gray, 1, 1, outputFile);
    }
    // Đóng các file
    fclose(inputFile);
    fclose(outputFile);
}
int main() {
    readImage("C:\\Users\\Admin\\Desktop\\Bai1\\lena.jpg", "C:\\Users\\Admin\\Desktop\\Bai1\\raw.dat");
    convertToGrayscale("C:\\Users\\Admin\\Desktop\\Bai1\\raw.dat", "C:\\Users\\Admin\\Desktop\\Bai1\\grayScale.dat");
    convertToBinary("C:\\Users\\Admin\\Desktop\\Bai1\\grayScale.dat", "C:\\Users\\Admin\\Desktop\\Bai1\\binaryImage.dat");
}