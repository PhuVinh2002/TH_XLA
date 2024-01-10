#include <stdio.h>
#include <stdlib.h>
int main(){
    // Mở file raw_gray.dat để đọc
    FILE *inputFile = fopen("C:\\Users\\Admin\\Desktop\\Bai4\\raw.dat", "rb");
    if (inputFile == NULL){
        perror("Không thể mở file raw.dat");
        return 1;
    }

    // Mở file raw_binary.dat để ghi dữ liệu binary
    FILE *outputFile = fopen("C:\\Users\\Admin\\Desktop\\Bai4\\raw_gray.dat", "wb");
    if (outputFile == NULL){
        perror("Không thể mở file raw_gray.dat");
        fclose(inputFile);
        return 1;
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
                return 1;
            }
        }
        unsigned char gray = (pixel[0] + pixel[1] + pixel[2])/3;

        // Ghi dữ liệu grayscale vào file raw_gray.dat

        fwrite(&gray, 1, 1, outputFile);
    }

    // Đóng các file
    fclose(inputFile);
    fclose(outputFile);

    return 0;

}