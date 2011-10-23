LOCAL_PATH := $(call my-dir)

include $(CLEAR_VARS)

LOCAL_MODULE    := jninio
LOCAL_SRC_FILES := jninio.c
LOCAL_LDLIBS    := -llog

include $(BUILD_SHARED_LIBRARY)
