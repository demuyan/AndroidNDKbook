#include <stdio.h>
#include <android/log.h>
#include "calcvals.h"

#define EXPORT __attribute__((visibility("default")))
#define LOG_TAG ("addVals")

#define LOGD(... ) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define LOGE(... ) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))

jint
addVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a + b;
}

jint
subVals( JNIEnv* env, jobject thiz, 
                                               jint a, jint b)
{
    return a - b;
}

jint
mulVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a * b;
}

jint
divVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a / b;
}


int jniRegisterNativeMethods(JNIEnv* env, const char* className,
    const JNINativeMethod* gMethods, int numMethods)
{
    jclass clazz;

    LOGD("Registering %s natives\n", className);
    clazz = (*env)->FindClass(env, className);
    if (clazz == NULL) {
        LOGD("Native registration unable to find class '%s'\n", className);
        return -1;
    }
    if ((*env)->RegisterNatives(env, clazz, gMethods, numMethods) < 0) {
        LOGD("RegisterNatives failed for '%s'\n", className);
        return -1;
    }
    return 0;
}



static JNINativeMethod sMethods[] = {
     /* name, signature, funcPtr */
    {"addVals", "(II)I", (void*)addVals},
    {"subVals", "(II)I", (void*)subVals},
    {"mulVals", "(II)I", (void*)mulVals},
    {"divVals", "(II)I", (void*)divVals},
};

EXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    jniRegisterNativeMethods(env, "com/example/calcval/MainActivity", sMethods, NELEM(sMethods));
    return JNI_VERSION_1_6;
}


