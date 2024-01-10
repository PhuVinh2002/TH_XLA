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
    plt.title("Grayscale Image")
    plt.axis("off")
    plt.show()

# Đường dẫn của tệp tin ảnh xám
gray_image_path = "C:\\Users\\Admin\\Desktop\\REVIEW_C\\result2.dat" 
gray_image_path1 = "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output1_gray.dat"
gray_image_path2 = "C:\\Users\\Admin\\Desktop\\REVIEW_C\\output3_gray.dat"
image_width =  256
image_height = 256 
# Hiển thị ảnh xám
display_grayscale_image(gray_image_path1, image_width, image_height)
display_grayscale_image(gray_image_path2, image_width, image_height)
display_grayscale_image(gray_image_path, image_width, image_height)




