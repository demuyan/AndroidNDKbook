#include <jni.h>
#include "calcvals.h"

jint
Java_com_example_calcval_MainActivity_addVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a + b;
}

jint
Java_com_example_calcval_MainActivity_subVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a - b;
}

jint
Java_com_example_calcval_MainActivity_mulVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a * b;
}

jint
Java_com_example_calcval_MainActivity_divVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a / b;
}

