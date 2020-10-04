from PIL import Image


def to_greyscale(img, img_path):
    rgb_img = img.convert('RGB')
    new_img = Image.new('RGB', img.size)

    for i in range(0, rgb_img.size[0]):
        for j in range(0, rgb_img.size[1]):
            pixel_rgb = rgb_img.getpixel((i, j))

            grey_val = int(pixel_rgb[0] * 0.3) + int(pixel_rgb[1] * 0.59) + int(pixel_rgb[2] * 0.11)

            new_img.putpixel((i, j), (grey_val, grey_val, grey_val))

    if not img_path == "":
        halves = img_path.split('.')
        new_img_path = halves[0] + "_grey." + halves[1]

        new_img.save(new_img_path)

    return new_img
