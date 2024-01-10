#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define Width 256
#define Height 256

double calculateDistance(unsigned char arr1[], unsigned char arr2[], int size) {
    double distance = 0.0;

    for (int i = 0; i < size; ++i) {
        distance += pow(arr2[i] - arr1[i], 2);
    }

    distance = sqrt(distance);

    return distance;
}

int main(){

    FILE *inputFileVector1 = fopen("C:\\Users\\Admin\\Desktop\\vector1.dat", "rb");
    FILE *inputFileVector2 = fopen("C:\\Users\\Admin\\Desktop\\vector2.dat", "rb");

    unsigned char result1[Width];
    unsigned char result2[Width];

    // Đọc dữ liệu file ảnh
    fread(result1, 1, Width, inputFileVector1);
    fread(result2, 1, Width, inputFileVector2);

    int size = Width;
    double distance = calculateDistance(result1,result2, size);
    printf("Khoang cach giua hai mang la: %f\n", distance);
    for (int i = 0; i < 20; i++)
    {
        printf("%d ",result1[i]);
    }
    printf("\n\n");
    for (int i = 0; i < 20; i++)
    {
        printf("%d ",result2[i]);
    }
    
    return 0;
}