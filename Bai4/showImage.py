import cv2
import numpy as np
import matplotlib.pyplot as plt


with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputVertical.dat', 'rb') as file:
    data1 = file.read()
with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputHorizotal.dat', 'rb') as file:
    data2 = file.read()
with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalDown.dat', 'rb') as file:
    data3 = file.read()
with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalUp.dat', 'rb') as file:
    data4 = file.read()

with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputVertical1.dat', 'rb') as file:
    data5 = file.read()
with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputHorizotal1.dat', 'rb') as file:
    data6 = file.read()
with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalDown1.dat', 'rb') as file:
    data7 = file.read()
with open('C:\\Users\\Admin\\Desktop\\Bai4\\outputDiagonalUp1.dat', 'rb') as file:
    data8 = file.read()


# Chuyển dữ liệu từ file thành mảng numpy
img_array1 = np.frombuffer(data1, dtype=np.uint8)
img_array2 = np.frombuffer(data2, dtype=np.uint8)
img_array3 = np.frombuffer(data3, dtype=np.uint8)
img_array4 = np.frombuffer(data4, dtype=np.uint8)
img_array5 = np.frombuffer(data5, dtype=np.uint8)
img_array6 = np.frombuffer(data6, dtype=np.uint8)
img_array7 = np.frombuffer(data7, dtype=np.uint8)
img_array8 = np.frombuffer(data8, dtype=np.uint8)

height = int(len(img_array1) ** 0.5)
width = height

img1 = img_array1.reshape(height, width)
img2 = img_array2.reshape(height, width)
img3 = img_array3.reshape(height, width)
img4 = img_array4.reshape(height, width)
img5 = img_array5.reshape(height, width)
img6 = img_array6.reshape(height, width)
img7 = img_array7.reshape(height, width)
img8 = img_array8.reshape(height, width)

# Hiển thị ảnh
plt.subplot(2, 5, 1), plt.imshow(img1, cmap='gray'), plt.title('Vertical')
plt.subplot(2, 5, 2), plt.imshow(img2, cmap='gray'), plt.title('Horizontal')
plt.subplot(2, 5, 3), plt.imshow(img3, cmap='gray'), plt.title('Diagonal Down')
plt.subplot(2, 5, 4), plt.imshow(img4, cmap='gray'), plt.title('Diagonal Up')
plt.subplot(2, 5, 6), plt.imshow(img5, cmap='gray'), plt.title('Vertical')
plt.subplot(2, 5, 7), plt.imshow(img6, cmap='gray'), plt.title('Horizontal')
plt.subplot(2, 5, 8), plt.imshow(img7, cmap='gray'), plt.title('Diagonal Down')
plt.subplot(2, 5, 9), plt.imshow(img8, cmap='gray'), plt.title('Diagonal Up')

plt.show()
