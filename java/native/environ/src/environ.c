#include "Environment.h"
#include <stdio.h>

extern char **environ;
static int index = 0;

JNIEXPORT jboolean JNICALL Java_Environment_hasMoreVariable(JNIEnv *env, jclass cl) {
  return environ[index] != NULL;
}

JNIEXPORT jstring JNICALL Java_Environment_getVariable(JNIEnv *env, jclass cl) {
  jstring ret = (*env)->NewStringUTF(env, environ[index++]);
  return ret;
}
