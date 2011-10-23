#include <jni.h>

#ifndef _addvals_h
#define _addvals_h
#ifdef __cplusplus
extern "C" {
#endif

    jint Java_com_example_nativebitmap_MainActivity_addVals( JNIEnv* env, jobject thiz, jobject bitmap, jint sx, jint sy, jint ex, jint ey);

#ifdef __cplusplus
}
#endif
#endif
