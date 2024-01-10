#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"  
#define Width 256
#define Height 256

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
void detectObject(const char* image_path1, const char* image_path2, const char* output_path) {
    FILE *inputFile1 = fopen(image_path1, "rb");
    FILE *inputFile2 = fopen(image_path2, "rb");
    FILE *outputFile = fopen(output_path, "wb");

    unsigned char image1[Width][Height];
    unsigned char image2[Width][Height];
    fread(image1, 1, Width * Height, inputFile1);
    fread(image2, 1, Width * Height, inputFile2);

    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Height; ++j) {
           unsigned char sub = abs(image1[i][j] - image2[i][j]);
           if (sub < 10 ) sub = 255;
           else sub = 0;
           fwrite(&sub, 1, 1, outputFile);
        }
    }
    fclose(inputFile1);
    fclose(inputFile2);
    fclose(outputFile);
}

typedef struct {
    float x;
    float y;
}Point;

Point findObjectPosition(const char* result_path) {
    FILE* resultFile = fopen(result_path, "rb");

    if (resultFile == NULL) {
        perror("Không thể mở file result.dat");
        Point invalidPoint = {0.0f, 0.0f};
        return invalidPoint;
    }

    unsigned char image[Width][Height];
    fread(image, 1, Width * Height, resultFile);
    fclose(resultFile);

    int objectCount = 0;
    int totalX = 0;
    int totalY = 0;

    for (int i = 0; i < Width; ++i) {
        for (int j = 0; j < Height; ++j) {
            if (image[i][j] == 0) {
                totalX += i;
                totalY += j;
                objectCount++;
            }
        }
    }
    if (objectCount > 0) {
        int centroidX = (totalY / objectCount);
        int centroidY = 256 - (totalX / objectCount);

        Point point;
        point.x = (float)centroidX;
        point.y = (float)centroidY;
        
        return point;
    } else {
        Point invalidPoint = {0.0f, 0.0f};
        return invalidPoint;
    }
}

int main() {
    readImage("C:\\Users\\Admin\\Desktop\\Bai6\\1.jpeg", "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output1.dat");
    readImage("C:\\Users\\Admin\\Desktop\\Bai6\\2.jpeg", "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output2.dat");
    readImage("C:\\Users\\Admin\\Desktop\\Bai6\\3.jpeg", "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output3.dat");
    convertToGrayscale("C:\\Users\\Admin\\Desktop\\REVIEW_C\\output1.dat", "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output1_gray.dat");
    convertToGrayscale("C:\\Users\\Admin\\Desktop\\REVIEW_C\\output2.dat", "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output2_gray.dat");
    convertToGrayscale("C:\\Users\\Admin\\Desktop\\REVIEW_C\\output3.dat", "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output3_gray.dat");
    detectObject("C:\\Users\\Admin\\Desktop\\REVIEW_C\\output1_gray.dat","C:\\Users\\Admin\\Desktop\\REVIEW_C\\output2_gray.dat","C:\\Users\\Admin\\Desktop\\REVIEW_C\\result1.dat");
    detectObject("C:\\Users\\Admin\\Desktop\\REVIEW_C\\output1_gray.dat","C:\\Users\\Admin\\Desktop\\REVIEW_C\\output3_gray.dat","C:\\Users\\Admin\\Desktop\\REVIEW_C\\result2.dat");
    Point object1Position = findObjectPosition("C:\\Users\\Admin\\Desktop\\REVIEW_C\\result2.dat");
    Point object2Position = findObjectPosition("C:\\Users\\Admin\\Desktop\\REVIEW_C\\result1.dat");

    printf("Toa do vat thoi diem 1 la: (%.1f, %.1f)\n",object1Position.x, object1Position.y);
    printf("Toa do vat thoi diem 2 la: (%.1f, %.1f)\n",object2Position.x, object2Position.y);
    
    float deltaX = object2Position.x - object1Position.x;
    float deltaY = object2Position.y - object1Position.y;
    float angle = atan2(deltaY, deltaX) * (180.0 / 3.14);
    if(angle > 0) {
        printf("Vat dang di chuyen ve phia truoc theo huong: %.0f degree\n", angle);
    }
    else if(angle < 0) {
        printf("Vat dang di lui theo huong: %d degree\n", abs(angle));
    }
    else {
        printf("Vat dang dang dung yen\n");
    }
    printf("Cach %d pixels so voi vi tri ban dau theo truc X", abs(deltaX));


    return 0;
}
