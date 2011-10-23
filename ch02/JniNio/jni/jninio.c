#include <stdio.h>
#include <android/log.h>
#include "jninio.h"

#define EXPORT __attribute__((visibility("default")))
#define LOG_TAG ("jninio")

#define LOGD(... ) ((void)__android_log_print(ANDROID_LOG_DEBUG, LOG_TAG, __VA_ARGS__))
#define LOGE(... ) ((void)__android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__))

typedef struct _DataInfo {
		int 	a;
		short b;
		char	c;
} DataInfo;

jint
setByteBuffer( JNIEnv* env, jobject thiz, jobject buf)
{
	DataInfo *dataInfo;

	dataInfo = (*env)->GetDirectBufferAddress(env, buf);

	LOGD("dataInfo->a=%d\n",dataInfo->a);
	LOGD("dataInfo->b=%d\n",dataInfo->b);
	LOGD("dataInfo->c=%d\n",dataInfo->c);

	dataInfo->a += 10;
	dataInfo->b += 10;
	dataInfo->c += 10;

    return 0;
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
    {"setByteBuffer", "(Ljava/nio/Buffer;)I", (void*)setByteBuffer},
};

EXPORT jint JNI_OnLoad(JavaVM* vm, void* reserved)
{
    JNIEnv* env = NULL;
    jint result = -1;

	if ((*vm)->GetEnv(vm, (void**) &env, JNI_VERSION_1_6) != JNI_OK) {
        return result;
    }

    jniRegisterNativeMethods(env, "com/example/jninio/MainActivity", sMethods, NELEM(sMethods));
    return JNI_VERSION_1_6;
}
