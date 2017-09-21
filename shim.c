/*
 * Native 'shim' to get KeyStore data,
 * run as the userid which you want to get 
 * the KeyStore data from.
 *
 * ex. $ run-as diff.example.packagename shim keystorename
 *
 * Tim 'diff' Strazzere
 *   <strazz@gmail.com>
 *
 *
 */

#include <stdlib.h> // avoid exit warning
#include <stdio.h>

#include <dlfcn.h>  // dlopen/dlclose
#include <unistd.h> // access
#include <jni.h>    // jni stuff

#include "vm.h"

int main(int argc, const char* argv[]) {
  printf("[*] keystore-snag - diff\n");
  if(argc < 2) {
    printf(" [!] Need an alias name to try and get data from!\n");
    return -1;
  }

  printf(" [+] Initializing JavaVM Instance\n");
  JavaVM *vm = NULL;
  JNIEnv *env = NULL;
  int status = init_jvm(&vm, &env);
  if (status == 0) {
    printf(" [+] Initialization success (vm=%p, env=%p)\n", vm, env);
  } else {
    printf(" [!] Initialization failure (%i: %s)\n", status, dlerror());
    return -1;
  }


  jclass clazz = (*env)->FindClass(env, "java.security.KeyStore");
  if(clazz == NULL) {
    printf(" [!] Error finding class");
  } else {
    printf(" [+] Found 'java.security.KeyStore' class (%p)\n", clazz);
  }

  // First get a ks object
  // KeyStore ks = KeyStore.getInstance(KeyStore.getDefaultType());
  jmethodID getDefaultType = (*env)->GetStaticMethodID(env, clazz, "getDefaultType", "()Ljava/lang/String;");
  if(getDefaultType == NULL) {
    printf(" [!] Error initializing getDefaultType method\n");
  } else {
    printf(" [+] Found getDefaultType method (%p)\n", getDefaultType);
  }

  jstring defaultType = (*env)->CallStaticObjectMethod(env, clazz, getDefaultType);
  if(defaultType == NULL) {
    printf(" [!] Issue getting default type for KeyStore objects!\n");
  } else {
    printf(" [+] Found default type of [ %s ]\n", (*env)->GetStringUTFChars(env, defaultType, JNI_FALSE));
  }

  jmethodID getInstance = (*env)->GetStaticMethodID(env, clazz, "getInstance", "(Ljava/lang/String;)Ljava/security/KeyStore;");
  if(getInstance == NULL) {
    printf(" [!] Error initializing getInstance method\n");
  } else {
    printf(" [+] Found getInstance method (%p)\n", getInstance);
  }

  jobject instance = (*env)->CallStaticObjectMethod(env, clazz, getInstance, defaultType);
  if(instance == NULL) {
    printf(" [!] Error retrieving an instnace of a KeyStore object!\n");
  } else {
    printf(" [+] Retreived instance (%p)\n", instance);
  }

  // getEntry(String alias, KeyStore.ProtectionParameter protParam) KeyStore.Entry
  jmethodID getEntry = (*env)->GetMethodID(env, clazz, "getEntry", "(Ljava/lang/String;Ljava/security/KeyStore$ProtectionParameter;)Ljava/security/KeyStore$Entry;");
  if(getEntry == NULL) {
    printf(" [!] Error initializing getEntry method\n");
  } else {
    printf(" [+] Found getEntry method (%p)\n", getEntry);
  }

  jobject protParam = NULL;
  jstring alias = (*env)->NewStringUTF(env, argv[1]);

  jobject keyStoreData = (*env)->CallObjectMethod(env, instance, getEntry, alias, protParam);
  if(keyStoreData == NULL) {
    printf(" [!] Error getting KeyStore data!\n");
  } else {
    printf(" [+] Got KeyStore data (%p)\n", keyStoreData);
  }
  return 0;
}
