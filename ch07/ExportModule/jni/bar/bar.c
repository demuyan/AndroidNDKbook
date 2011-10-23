#include <jni.h>
#include "bar.h"

jint  Java_com_example_exportmodule_MainActivity_fooval(JNIEnv* env, jobject thiz)
{
    return FOO;
}

jint  Java_com_example_exportmodule_MainActivity_foofunc(JNIEnv* env, jobject thiz)
{
    return foo();
}
