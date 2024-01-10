import numpy as np
import matplotlib.pyplot as plt

def display_grayscale_image(file_path, width, height):
    # Đọc dữ liệu từ tệp tin vào mảng NumPy
    with open(file_path, 'rb') as file:
        grayscale_data = np.fromfile(file, dtype=np.uint8, count=width * height)

    # Chuyển đổi mảng NumPy thành hình ảnh 2D
    grayscale_image = grayscale_data.reshape((height, width))

    # Hiển thị ảnh xám
    plt.imshow(grayscale_image, cmap='gray')
    plt.axis("off")
    plt.show()

# Đường dẫn của tệp tin ảnh
gray_image_path = "C:\\Users\\Admin\\Desktop\\Bai2\\edgeImage.dat" 

image_width =  256
image_height = 256 
# Hiển thị ảnh
display_grayscale_image(gray_image_path, image_width, image_height)




