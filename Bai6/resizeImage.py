
import cv2
import numpy as np

# Đọc ảnh màu bất kì

path = r'C:\\Users\\Admin\\Desktop\\Bai6\\3.jpeg'

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

