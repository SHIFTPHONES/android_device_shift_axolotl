LOCAL_PATH := $(call my-dir)

#----------------------------------------------------------------------
# Generate persist image (persist.img)
#----------------------------------------------------------------------
TARGET_OUT_PERSIST_IMG_PATH := $(PRODUCT_OUT)/persist

INTERNAL_PERSISTIMAGE_FILES := \
    $(foreach pair,$(PRODUCT_COPY_FILES),\
        $(if $(filter persist/%,$(call word-colon,2,$(pair))),\
            $(call word-colon,1,$(pair)):$(PRODUCT_OUT)/$(call word-colon,2,$(pair))))

INSTALLED_PERSISTIMAGE_FILES := $(call copy-many-files,$(INTERNAL_PERSISTIMAGE_FILES))
INSTALLED_PERSISTIMAGE_TARGET := $(PRODUCT_OUT)/persist.img

$(INSTALLED_PERSISTIMAGE_TARGET): $(MKEXTUSERIMG) $(MAKE_EXT4FS) $(INSTALLED_PERSISTIMAGE_FILES)
	$(call pretty,"Target persist fs image: $(INSTALLED_PERSISTIMAGE_TARGET)")
	@mkdir -p $(TARGET_OUT_PERSIST_IMG_PATH)
	$(hide) PATH=$(HOST_OUT_EXECUTABLES):$${PATH} $(MKEXTUSERIMG) -s $(TARGET_OUT_PERSIST_IMG_PATH) $@ ext4 persist $(BOARD_PERSISTIMAGE_PARTITION_SIZE)
	$(hide) chmod a+r $@
	$(hide) $(call assert-max-image-size,$@,$(BOARD_PERSISTIMAGE_PARTITION_SIZE))

ALL_DEFAULT_INSTALLED_MODULES += $(INSTALLED_PERSISTIMAGE_TARGET)
ALL_MODULES.$(LOCAL_MODULE).INSTALLED += $(INSTALLED_PERSISTIMAGE_TARGET)

.PHONY: persistimage
persistimage: $(INSTALLED_PERSISTIMAGE_TARGET)

droidcore: $(INSTALLED_PERSISTIMAGE_TARGET)

#----------------------------------------------------------------------
# Generate metadata image (metadata.img)
# As of now this in empty at build and data is runtime generated only,
# so create an empty fs
#----------------------------------------------------------------------
TARGET_OUT_METADATA_IMG_PATH := $(PRODUCT_OUT)/metadata

INSTALLED_METADATAIMAGE_TARGET := $(PRODUCT_OUT)/metadata.img

$(INSTALLED_METADATAIMAGE_TARGET): $(MKEXTUSERIMG) $(MAKE_EXT4FS)
	$(call pretty,"Target metadata fs image: $(INSTALLED_METADATAIMAGE_TARGET)")
	@mkdir -p $(TARGET_OUT_METADATA_IMG_PATH)
	$(hide)PATH=$(HOST_OUT_EXECUTABLES):$${PATH} $(MKEXTUSERIMG) -s $(TARGET_OUT_METADATA_IMG_PATH) $@ ext4 metadata $(BOARD_METADATAIMAGE_PARTITION_SIZE)
	$(hide) chmod a+r $@
	$(hide) $(call assert-max-image-size,$@,$(BOARD_METADATAIMAGE_PARTITION_SIZE))

ALL_DEFAULT_INSTALLED_MODULES += $(INSTALLED_METADATAIMAGE_TARGET)
ALL_MODULES.$(LOCAL_MODULE).INSTALLED += $(INSTALLED_METADATAIMAGE_TARGET)

.PHONY: metadataimage
metadataimage: $(INSTALLED_METADATAIMAGE_TARGET)

droidcore: $(INSTALLED_METADATAIMAGE_TARGET)
