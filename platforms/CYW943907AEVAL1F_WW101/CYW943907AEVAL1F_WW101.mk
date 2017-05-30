#
# $ Copyright Broadcom Corporation $
#
PLATFORM_NAME            := CY943907AEVAL1F
WLAN_CHIP                := 43909
WLAN_CHIP_REVISION       := B0
WLAN_CHIP_FAMILY         := 4390x
HOST_MCU_FAMILY          := BCM4390x
HOST_MCU_VARIANT         := BCM43907
HOST_MCU_PART_NUMBER     := BCM43907WLCSPR

DEFAULT_BOARD_REVISION   := P202
BOARDS_WITH_B1_CHIP      := P202
SUPPORTED_BOARD_REVISION := $(BOARDS_WITH_B1_CHIP)
BOARD_REVISION_DIR       := board_revision
#if no board revision specified in build string
ifeq ($(BOARD_REVISION),)
BOARD_REVISION           := $(DEFAULT_BOARD_REVISION)
endif

ifneq ($(filter $(BOARD_REVISION), $(BOARDS_WITH_B0_CHIP)),)
APPS_CHIP_REVISION       := B0
else ifneq ($(filter $(BOARD_REVISION), $(BOARDS_WITH_B1_CHIP) $(BOARDS_WITH_B2_CHIP) ),)
APPS_CHIP_REVISION       := B1
endif

NAME                     := Platform_$(PLATFORM_NAME)_$(BOARD_REVISION)_$(APPS_CHIP_REVISION)

PLATFORM_SUPPORTS_BUTTONS := 1

PLATFORM_NO_USB_HOST := 1
PLATFORM_NO_DDR      := 1

GLOBAL_DEFINES += SFLASH_SUPPORT_MACRONIX_PARTS

PLATFORM_SOURCES := $(SOURCE_ROOT)platforms/$(PLATFORM_DIRECTORY)/

$(NAME)_SOURCES := platform.c

GLOBAL_INCLUDES := . \
                   ./$(BOARD_REVISION_DIR)/$(BOARD_REVISION)
