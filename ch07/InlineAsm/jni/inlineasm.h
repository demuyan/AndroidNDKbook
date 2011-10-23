#include <jni.h>

#ifndef _addvals_h
#define _addvals_h
#ifdef __cplusplus
extern "C" {
#endif

    jint Java_com_example_calcval_MainActivity_addVals( JNIEnv* env, jobject thiz,jint a, jint b);
    jint Java_com_example_calcval_MainActivity_subVals( JNIEnv* env, jobject thiz,jint a, jint b);
    jint Java_com_example_calcval_MainActivity_mulVals( JNIEnv* env, jobject thiz,jint a, jint b);
    jint Java_com_example_calcval_MainActivity_divVals( JNIEnv* env, jobject thiz,jint a, jint b);

#ifdef __cplusplus
}
#endif
#endif
