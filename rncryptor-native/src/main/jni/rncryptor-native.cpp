/*
 * Copyright (C) 2016 Giorgi TGIO Tabatadze
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "rncryptor-native.h"
#include <string>
#include "cryptopp/modes.h"
#include "cryptopp/aes.h"
#include "cryptopp/filters.h"
#include "rndecryptor.h"
#include "rnencryptor.h"

using namespace std;

void log(const char *tag, const char *message);

using CryptoPP::AES;
using CryptoPP::CBC_Mode_ExternalCipher;
using CryptoPP::StreamTransformationFilter;
using CryptoPP::StringSink;
using CryptoPP::SimpleKeyingInterface;
using namespace std;

jstring
Java_tgio_rncryptor_RNCryptorNative_getABI(JNIEnv *env, jobject thiz) {
#if defined(__arm__)
#if defined(__ARM_ARCH_7A__)
#if defined(__ARM_NEON__)
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a/NEON (hard-float)"
#else
#define ABI "armeabi-v7a/NEON"
#endif
#else
#if defined(__ARM_PCS_VFP)
#define ABI "armeabi-v7a (hard-float)"
#else
#define ABI "armeabi-v7a"
#endif
#endif
#else
#define ABI "armeabi"
#endif
#elif defined(__i386__)
#define ABI "x86"
#elif defined(__x86_64__)
#define ABI "x86_64"
#elif defined(__mips64)  /* mips64el-* toolchain defines __mips__ too */
#define ABI "mips64"
#elif defined(__mips__)
#define ABI "mips"
#elif defined(__aarch64__)
#define ABI "arm64-v8a"
#else
#define ABI "unknown"
#endif
    return (env)->NewStringUTF(ABI);
}

jbyteArray Java_tgio_rncryptor_RNCryptorNative_encrypt(JNIEnv *env, jobject instance, jbyteArray raw_, jstring password_) {
    jbyte* raw = env->GetByteArrayElements(raw_, NULL);
    jsize raw_size = env->GetArrayLength(raw_);
    string data((const char*)raw, raw_size);

    const char *password = env->GetStringUTFChars(password_, 0);
    RNEncryptor *encryptor = new RNEncryptor();
    string encrypted = encryptor->encrypt(data, password);
    delete encryptor;
    env->ReleaseByteArrayElements(raw_, raw, JNI_ABORT);
    env->ReleaseStringUTFChars(password_, password);
    jbyteArray array = env->NewByteArray(encrypted.size());
    env->SetByteArrayRegion(array, 0, encrypted.size(), (const jbyte *) encrypted.c_str());

    return array;
}


jbyteArray Java_tgio_rncryptor_RNCryptorNative_decrypt(JNIEnv *env, jobject instance, jbyteArray encrypted_, jstring password_) {
    string decrypted = "0";
    if (encrypted_ != NULL) {
        try {
            jbyte* encrypted = env->GetByteArrayElements(encrypted_, NULL);
            jsize encrypted_size = env->GetArrayLength(encrypted_);
            string encrypted_data((const char*)encrypted, encrypted_size);

            const char *password = env->GetStringUTFChars(password_, 0);
            RNDecryptor *cryptor = new RNDecryptor();
            decrypted = cryptor->decrypt(encrypted_data, password);
            delete cryptor;
            env->ReleaseByteArrayElements(encrypted_, encrypted, JNI_ABORT);
            env->ReleaseStringUTFChars(password_, password);
        } catch (exception e) {
            decrypted = "error decrypting";
        }
    }
    jbyteArray array = env->NewByteArray(decrypted.size());
    env->SetByteArrayRegion(array, 0, decrypted.size(), (const jbyte *) decrypted.c_str());
    return array;
}