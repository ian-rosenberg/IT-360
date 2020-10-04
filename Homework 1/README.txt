There are command line arguments for this image processing program.
They include:
	--old_img 		Path to original image for processing
	--avg_filter_size 	Width & Height for the filter (integer)
	--gauss_filter_size	3 or 5 for the two filter presets
	--circle_radius		Radius for the circle drawing program


Notes: 
scale_down only scales an image down by a factor of 2, so half the width and height.
Did not put in error checking for missing arguments, just created a minimum viable product.