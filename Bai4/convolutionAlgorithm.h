// #ifdef algorithm

#define Width 256
#define Height 256

void padImage(unsigned char image[Width][Height], unsigned char padImage[Width + 2][Height + 2]){
    // Padding giá trị 0 ở các cạnh 
    for (int i = 0; i < Width + 2; ++i) {
        for (int j = 0; j < Height + 2; ++j) {
            if (i == 0 || j == 0 || i == Width + 1 || j == Height + 1) {
                padImage[i][j] = 0; // Thêm giá trị  0
            } else {
                padImage[i][j] = image[i - 1][j - 1]; // Copy ảnh vào ở giữa
            }
        }
    }
}

void convolution(unsigned char image[Width][Height], int kernel[3][3], int result[Width][Height]) {

    int i, j, m, n;
    int sum;

    unsigned char tempImage[Width + 2][Height + 2];
    padImage(image,tempImage);

    // Nhân chập với kernel
    for (i = 1; i <= Width; ++i) {
        for (j = 1; j <= Height; ++j) {
            sum = 0;
            for (m = -1; m <= 1; ++m) {
                for (n = -1; n <= 1; ++n) {
                    sum += kernel[m + 1][n + 1] * tempImage[j + m][i + n];
                }
            }
            if(sum > 255){
                sum = 255;
            }
            if(sum < 0){
                sum = 0;
            }
                result[j - 1][i - 1] = sum;       
        }
    }
}
// #endif