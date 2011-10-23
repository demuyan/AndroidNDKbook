#include <jni.h>

#ifndef _addvals_h
#define _addvals_h
#ifdef __cplusplus
extern "C" {
#endif

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

jint addVals( JNIEnv* env, jobject thiz, jint a, jint b);
jint subVals( JNIEnv* env, jobject thiz, jint a, jint b);
jint mulVals( JNIEnv* env, jobject thiz, jint a, jint b);
jint divVals( JNIEnv* env, jobject thiz, jint a, jint b);

#ifdef __cplusplus
}
#endif
#endif
