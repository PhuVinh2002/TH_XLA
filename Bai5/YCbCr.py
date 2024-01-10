from PIL import Image
import numpy as np
import cv2

path = r'C:\Users\Admin\Desktop\Bai5\lena.jpg'

# Đọc ảnh
Img = cv2.imread(path, cv2.IMREAD_COLOR)
img = Image.open(path)
# Tạo mode và size ảnh
YCbCr444 = Image.new(img.mode, img.size)
YCbCr422 = Image.new(img.mode, img.size)

width, height = img.size

# Chuyển RGB sang YCrCb và 4:4:4 -> 4:2:2
for x in range(width):
    for y in range(height):
        R, G, B = img.getpixel((x, y))
        kY = np.uint8(16 + (65.738 * R / 256) + (129.057 * G / 256) + (25.064 * B / 256))
        kCr = np.uint8(128 - (37.945 * R / 256) - (74.494 * G / 256) + (112.439 * B / 256))
        kCb = np.uint8(128 + (112.439 * R / 256) - (94.154 * G / 256) - (18.285 * B / 256))

        YCbCr444.putpixel((x, y), (kY, kCr, kCb))

        # 4:4:4 -> 4:2:2
        if (x % 2 == 0):
            YCbCr422.putpixel((x, y), (kY, kCr, kCb))
        else:
            YCbCr422.putpixel((x, y), (kY, kY, kY))

# 4:2:2 -> 4:4:4
reYCbCr444 = YCbCr422.copy()
for x in range(width):
    for y in range(height):
        R, G, B = img.getpixel((x, y))
        kY = np.uint8(16 + (65.738 * R / 256) + (129.057 * G / 256) + (25.064 * B / 256))
        kCr = np.uint8(128 - (37.945 * R / 256) - (74.494 * G / 256) + (112.439 * B / 256))
        kCb = np.uint8(128 + (112.439 * R / 256) - (94.154 * G / 256) - (18.285 * B / 256))

        if reYCbCr444.getpixel((x, y)) == (kY, kY, kY):
            reYCbCr444.putpixel((x, y), (kY, kCr, kCb))

# 4:4:4 -> RGB
reRGB = Image.new(img.mode, img.size)
for x in range(width):
    for y in range(height):
        kY, kCr, kCb = reYCbCr444.getpixel((x, y))
        R = np.uint8(max(0, min((kY * 298.082 / 256) + (kCr * 408.583 / 256) - 222.921, 255)))
        G = np.uint8(max(0, min((kY * 298.082 / 256) - (kCb * 100.291 / 256) - (kCr * 208.120 / 256) + 135.576, 255)))
        B = np.uint8(max(0, min((kY * 298.082 / 256) + (kCb * 516.412 / 256) - 276.836, 255)))

        reRGB.putpixel((x, y), (R, G, B))

#img = np.array(img)
YCbCr444 = np.array(YCbCr444)
YCbCr422 = np.array(YCbCr422)
reYCbCr444 = np.array(reYCbCr444)
reRGB = np.array(reRGB)

cv2.imshow('RGB', Img)
cv2.imshow('YCrCb 4:4:4', YCbCr444)
cv2.imshow('YCrCb 4:2:2', YCbCr422)
cv2.imshow('ReYCrCb 4:4:4', reYCbCr444)
cv2.imshow('ReRGB', reRGB)

cv2.waitKey(0)
cv2.destroyAllWindows()
