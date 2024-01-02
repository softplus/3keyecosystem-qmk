# unique to kai6 device

RGB_MATRIX_ENABLE = yes		# Enable RGB matrix

# This overrides the default ws2812
RGB_MATRIX_DRIVER = custom	# Select WS2812 driver for RGB matrix
SRC += ledpins_as_matrix/ledpins_as_matrix.c	# ... and add our custom code for the LED driver
