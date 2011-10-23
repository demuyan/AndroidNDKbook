#include <jni.h>

#ifndef _addvals_h
#define _addvals_h
#ifdef __cplusplus
extern "C" {
#endif

#ifndef NELEM
# define NELEM(x) ((int) (sizeof(x) / sizeof((x)[0])))
#endif

jint setByteBuffer( JNIEnv* env, jobject thiz, jobject b);

#ifdef __cplusplus
}
#endif
#endif
