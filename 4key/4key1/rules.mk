# unique to this version of hardware

LED_MATRIX_ENABLE = yes		# Enable LED matrix for key lights
LED_MATRIX_DRIVER = custom	# Use our custom pin-mapped LED driver
SRC += ../common/custom_led_pins.c	# ... and add our custom code for the LED driver
