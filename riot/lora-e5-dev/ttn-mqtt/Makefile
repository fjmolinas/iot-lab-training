# name of the application
APPLICATION = ttn-mqtt

# The default board is LoRa-E5-Dev LoRa discovery board
BOARD ?= lora-e5-dev

RIOTBASE ?= $(CURDIR)/../../RIOT

#
# Here we add the modules that are needed
#
USEMODULE += xtimer
USEMODULE += lm75a


#
# The application needs LoRaWAN related modules and variables:
#
USEMODULE += auto_init_loramac

# The Semtech LoRa radio device (SX126X)
USEMODULE += sx126x_stm32wl
USEMODULE += sx1276

# The Semtech Loramac package
USEPKG += semtech-loramac

# Default region is Europe and default band is 868MHz
LORA_REGION ?= EU868

# This must be the last line of the Makefile
include $(RIOTBASE)/Makefile.include
