from PIL import Image
from Avgfilter import average_filter
from Grey import to_greyscale
from GaussSample import gauss
from Laplace import laplace
from Circle import circle
from ScaleDown import scale_down
import argparse


def main():
    # CMD argument parsing
    parser = argparse.ArgumentParser()
    parser.add_argument('--old_img')
    parser.add_argument('--avg_filter_size')
    parser.add_argument('--gauss_filter_size')
    parser.add_argument('--circle_radius')
    args = parser.parse_args()

    old_img_path = args.old_img
    avg_filter_size = args.avg_filter_size
    gauss_filter_size = args.gauss_filter_size
    circle_radius = args.circle_radius

    if type(old_img_path) is not str:
        print("Original image path is not a string!")
        return

    old_image = Image.open(old_img_path)

    to_greyscale(old_image, old_img_path)

    average_filter(old_image, old_img_path, avg_filter_size)

    gauss(old_image, old_img_path, gauss_filter_size)

    laplace(old_image, old_img_path)

    circle(circle_radius)

    scale_down(old_image, old_img_path)


if __name__ == '__main__':
    main()
