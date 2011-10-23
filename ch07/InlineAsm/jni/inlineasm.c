#include <jni.h>
#include "inlineasm.h"

jint
Java_com_example_inlineasm_MainActivity_addVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    int ret=0;

    __asm__ __volatile__  (
      "add %[result], %[val1],%[val2]\n\t"
    : [result]"=r"(ret)
    : [val1]"r"(a), [val2]"r"(b)
    );

    return ret;
}

jint
Java_com_example_inlineasm_MainActivity_subVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a - b;
}

jint
Java_com_example_inlineasm_MainActivity_mulVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a * b;
}

jint
Java_com_example_inlineasm_MainActivity_divVals( JNIEnv* env, jobject thiz,
                                               jint a, jint b)
{
    return a / b;
}

