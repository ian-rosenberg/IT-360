from Grey import to_greyscale
from PIL import Image
from GaussSample import gauss
from Avgfilter import clamp_int

filter_3 = [[0, 1, 0],
          [1, -4, 1],
          [0, 1, 0]]


# add up neighbors multiplied by filter -> new pixel val
# Take extrema from new pixel vals
# Normalize
def laplace(orig_img, img_path):
    grey_scale = to_greyscale(orig_img, img_path)

    new_pixels = Image.new('RGB', (grey_scale.size[0], grey_scale.size[1]))

    extrema = [255, 0]

    calc_pixels = []

    r = 0

    for x in range(0, grey_scale.size[0]):
        calc_pix_row = []
        for y in range(0, grey_scale.size[1]):
            for cell_row in range(0, len(filter_3)):
                for cell_col in range(0, len(filter_3[cell_row])):
                    new_x = clamp_int(0, grey_scale.size[0], x + cell_col - 1)
                    new_y = clamp_int(0, grey_scale.size[1], y + cell_row - 1)

                    pix = grey_scale.getpixel((new_x, new_y))

                    r += pix[0] * filter_3[cell_row][cell_col]

            calc_pix_row.append(r)
            extrema[0] = min(calc_pix_row)
            extrema[1] = max(calc_pix_row)
            r = 0
        calc_pixels.append(calc_pix_row)

    for x in range(0, len(calc_pixels)):
        for y in range(0, len(calc_pixels[x])):
            r = int(255 * (calc_pixels[x][y] - extrema[0]) / (extrema[1] - extrema[0]))

            new_pixels.putpixel((x, y), (r, r, r))

    new_pixels.show(new_pixels.size)

    halves = img_path.split('.')
    new_img_path = halves[0] + "_laplace" + "." + halves[1]

    new_pixels.save(new_img_path)