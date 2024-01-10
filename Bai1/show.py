import numpy as np
import matplotlib.pyplot as plt

def load_image_from_dat(file_path):
    # Đọc kích thước từ file .dat
    with open(file_path, 'rb') as file:
        width = np.fromfile(file, dtype=np.int32, count=1)[0]
        height = np.fromfile(file, dtype=np.int32, count=1)[0]

        # Đọc dữ liệu từ file .dat
        data = np.fromfile(file, dtype=np.uint8)

    # Reshape dữ liệu thành mảng 3D (chiều cao x chiều rộng x 3)
    image = data.reshape((height, width, 3))

    plt.imshow(image)
    plt.axis('off')
    plt.show()

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

# Thay đổi đường dẫn tới file .dat và kích thước của ảnh
file_path = 'C:\\Users\\Admin\\Desktop\\Bai1\\binaryImage.dat'

# Load và hiển thị ảnh
# load_image_from_dat(file_path)
display_grayscale_image(file_path,256,256)
