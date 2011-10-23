LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := calcvals
LOCAL_SRC_FILES := calcvals.c

include $(BUILD_SHARED_LIBRARY)
