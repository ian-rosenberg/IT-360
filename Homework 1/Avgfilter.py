from PIL import Image
import numpy as np


def clamp_int(min_val, max_val, val):
    if val < min_val:
        return min_val
    if val >= max_val:
        return max_val - 1
    return val


def average_filter(img, img_path, filter_size):
    if int(filter_size) % 2 != 1:
        print("Filter size must be an odd number!")
        return

    filter_size = int(filter_size)

    r = 0
    g = 0
    b = 0

    rgb_img = img.convert('RGB')
    new_pixels = Image.new('RGB', (rgb_img.size[0], rgb_img.size[1]))

    for x in range(0, rgb_img.size[0]):
        pixel_rows = []

        for y in range(0, rgb_img.size[1]):
            neighbors = []

            for cell_col in range(int(filter_size / 2) * -1, int(filter_size / 2) + 1):
                neighbor_row = []
                for cell_row in range(int(filter_size / 2) * -1, int(filter_size / 2) + 1):
                    new_x = x
                    new_y = y

                    new_x = clamp_int(0, rgb_img.size[0], x + cell_col)
                    new_y = clamp_int(0, rgb_img.size[1], y + cell_row)

                    pix = rgb_img.getpixel((new_x, new_y))

                    neighbor_row.append(pix)

                    r += pix[0]
                    g += pix[1]
                    b += pix[2]

            r = r / np.square(filter_size)
            g = g / np.square(filter_size)
            b = b / np.square(filter_size)

            r = int(r)
            g = int(g)
            b = int(b)

            new_pixels.putpixel((x, y), (r, g, b))

            r = 0
            g = 0
            b = 0

    halves = img_path.split('.')
    new_img_path = halves[0] + "_avg_filter_" + str(filter_size) + "." + halves[1]

    new_pixels.save(new_img_path)

    return
