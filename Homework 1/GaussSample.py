from PIL import Image
from Avgfilter import clamp_int

filter_size_3 = [[1, 2, 1],
                 [2, 4, 2],
                 [1, 2, 1]]

filter_size_5 = [[2, 4, 5, 4, 2],
                 [4, 9, 12, 9, 4],
                 [5, 12, 15, 12, 5],
                 [4, 9, 12, 9, 4],
                 [2, 4, 5, 4, 2]]


def gauss(img, img_path, filter_width):
    if int(filter_width) != 3:
        if int(filter_width) != 5:
            print("Gauss filter size must be either 3 or 5!")
            return
    filter_width = int(filter_width)

    r = 0
    g = 0
    b = 0

    rgb_img = img.convert('RGB')
    new_pixels = Image.new('RGB', (rgb_img.size[0], rgb_img.size[1]))

    for x in range(0, rgb_img.size[0]):
        for y in range(0, rgb_img.size[1]):

            if filter_width == 3:
                for cell_col in range(int(len(filter_size_3) / 2) * -1, int(len(filter_size_3) / 2) + 1):
                    for cell_row in range(int(len(filter_size_3[cell_col]) / 2) * -1, int(len(filter_size_3[cell_col]) / 2) + 1):
                        new_x = clamp_int(0, rgb_img.size[0], x + cell_col)
                        new_y = clamp_int(0, rgb_img.size[1], y + cell_row)

                        pix = rgb_img.getpixel((new_x, new_y))

                        r += pix[0] * filter_size_3[cell_col][ cell_row]
                        g += pix[1] * filter_size_3[cell_col][cell_row]
                        b += pix[2] * filter_size_3[cell_col][cell_row]

            else:
                for cell_col in range(int(len(filter_size_5) / 2) * -1, int(len(filter_size_5) / 2) + 1):
                    for cell_row in range(int(len(filter_size_5[cell_col]) / 2) * -1, int(len(filter_size_5[cell_col]) / 2) + 1):
                        new_x = x
                        new_y = y

                        new_x = clamp_int(0, rgb_img.size[0], x + cell_col)
                        new_y = clamp_int(0, rgb_img.size[1], y + cell_row)

                        pix = rgb_img.getpixel((new_x, new_y))

                        in_x = int(len(filter_size_5) / 2) + cell_col - 1
                        in_y = int(len(filter_size_5) / 2) + cell_row - 1

                        r += pix[0] * filter_size_5[in_x][in_y]
                        g += pix[1] * filter_size_5[in_x][in_y]
                        b += pix[2] * filter_size_5[in_x][in_y]

            if filter_width == 3:
                r = r * (1/16)
                g = g * (1/16)
                b = b * (1/16)
            elif filter_width == 5:
                r = r * (1/159)
                g = g * (1/159)
                b = b * (1/159)

            r = int(r)
            g = int(g)
            b = int(b)

            new_pixels.putpixel((x, y), (r, g, b))

            r = 0
            g = 0
            b = 0

    new_pixels.show()

    halves = img_path.split('.')
    new_img_path = halves[0] + "_gauss_" + str(filter_width) + "." + halves[1]

    new_pixels.save(new_img_path)

    return new_pixels




