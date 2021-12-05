# unique to kai6 device

#LED_MATRIX_ENABLE = yes		# Enable LED matrix for key lights
#LED_MATRIX_DRIVER = custom	# Use our custom pin-mapped LED driver
RGB_MATRIX_ENABLE = yes		# Enable RGB matrix
RGB_MATRIX_DRIVER = custom	# Select WS2812 driver for RGB matrix
# our special driver
SRC += ../common/ledpins_as_matrix.c	# ... and add our custom code for the LED driver
