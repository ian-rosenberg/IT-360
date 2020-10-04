from PIL import Image
import numpy as np


def clamp_int(min_val, max_val, val):
    if val < min_val:
        return min_val
    if val >= max_val:
        return max_val - 1
    return val


def scale_down(old_img, old_img_path):
    rgb_img = old_img.convert('RGB')
    new_img = Image.new('RGB', (rgb_img.size[0] // 2, rgb_img.size[1] // 2))

    for x in range(0, rgb_img.size[0]):
        for y in range(0, rgb_img.size[1]):
            neighbors_r = []
            neighbors_g = []
            neighbors_b = []
            for cell_col in range(0, 2):
                for cell_row in range(0, 2):
                    new_x = clamp_int(0, rgb_img.size[0], x + cell_col)
                    new_y = clamp_int(0, rgb_img.size[1], y + cell_row)

                    neighbors_r.append(rgb_img.getpixel((new_x, new_y))[0])
                    neighbors_g.append(rgb_img.getpixel((new_x, new_y))[1])
                    neighbors_b.append(rgb_img.getpixel((new_x, new_y))[2])

            r = int(np.average(neighbors_r))
            g = int(np.average(neighbors_g))
            b = int(np.average(neighbors_b))

            new_img.putpixel((x//2, y//2), (r, g, b))

    new_img.show()

    halves = old_img_path.split('.')
    new_img_path = halves[0] + "_scaleDown" + "." + halves[1]

    new_img.save(new_img_path)

