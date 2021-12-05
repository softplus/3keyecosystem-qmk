# unique to kai6 hardware

RGB_MATRIX_ENABLE = yes		# Enable RGB matrix
RGB_MATRIX_DRIVER = custom	# Select WS2812 driver for RGB matrix
SRC += ../common/ledpins_as_matrix.c	# ... and add our custom code for the LED driver
