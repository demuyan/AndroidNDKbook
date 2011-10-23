#include <jni.h>
#include <android/log.h>

#include <android/bitmap.h>
#include "nativebitmap.h"

#define  LOG_TAG    ("nativebitmap")
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

void reverse(AndroidBitmapInfo* info, void* pixels){

    unsigned short* picbuf = pixels;
    int x,y;
    for (y = 0; y < info->height; y++){
        for (x = 0; x < info->width; x++){
            picbuf[y*info->width+x] ^= 0xffff;
        }
    }
}

void
Java_com_example_nativebitmap_MainActivity_reverseImage( JNIEnv* env, jobject thiz,
                                               jobject bitmap)
{
    AndroidBitmapInfo info;

    if (0 > AndroidBitmap_getInfo(env, bitmap, &info)){
        LOGE("AndroidBitmap_getInfo() failed !");
        return;
    }
    LOGI("imagesize(%d,%d)\n",info.width, info.height);

    if (info.format != ANDROID_BITMAP_FORMAT_RGB_565) {
        LOGE("Bitmap format is not RGB_565 : %d\n",info.format);
        return;
    }

    LOGI("before lockpixels\n");

    void* pixels;
    if (0 > AndroidBitmap_lockPixels(env, bitmap, &pixels)) {
        LOGE("AndroidBitmap_lockPixels() failed !");
        return;
    }

    reverse(&info, pixels);

    LOGI("after lockpixels\n");

    AndroidBitmap_unlockPixels(env, bitmap);
}
