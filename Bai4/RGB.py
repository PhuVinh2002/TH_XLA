
import cv2
import numpy as np

# Đọc ảnh màu bất kì

path = r'C:\\Users\\Admin\\Desktop\\Bai4\\4.jpg'

image = cv2.imread(path)
cv2.imshow('ẢNH RGB',image)
cv2.waitKey()

# Kiểm tra xem ảnh có tồn tại hay không
if image is None:
    print("Không thể đọc ảnh.")
else:
    # Lấy kích thước của ảnh
    height, width, channels = image.shape

    print('Kich thuoc anh la: ', image.shape)

    # Đặt lại kích thước ảnh
    height = 256
    width = 256

    resized_image = cv2.resize(image, (height,width))

    #Lưu hình ảnh sau khi change
    cv2.imwrite(path,resized_image)
    image = cv2.imread(path)
    print('Kich thuoc anh sau khi doi la: ',image.shape)
    
    height, width, channels = image.shape

    # Mở file để lưu trữ dữ liệu raw
    with open(r'C:\Users\Admin\Desktop\Bai4\raw1.dat', 'wb') as f:
        for y in range(height):
            for x in range(width):
                # Lấy giá trị màu B, G, R của từng pixel
                blue, green, red = image[y, x]
                # Ghi dữ liệu màu R, G, B vào file raw.dat
                f.write(bytes([red, green, blue]))

    print("Dữ liệu màu đã được lưu vào raw.dat.")
