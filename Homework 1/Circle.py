from PIL import Image
import numpy as np


def distance_from_center(x, y, r):
    return np.sqrt(np.abs(np.square(y - r) + np.square(x - r)))


def circle(radius):
    if int(radius) < 1:
        print("Needs a positive integer radius.")
        return

    radius = int(radius)

    file_path = "circle.jpg"
    new_pixels = Image.new('RGB', (radius * 2, radius * 2))

    for x in range(0, new_pixels.size[0]):
        for y in range(0, new_pixels.size[1]):
            if int(distance_from_center(x, y, radius)) < int(radius):
                new_pixels.putpixel((x, y), (0, 0, 0))
            else:
                new_pixels.putpixel((x, y), (255, 255, 255))

    new_pixels.save(file_path)

    return new_pixels
