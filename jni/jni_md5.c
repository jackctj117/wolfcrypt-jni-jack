/* jni_md5.c
 *
 * Copyright (C) 2006-2016 wolfSSL Inc.
 *
 * This file is part of wolfSSL. (formerly known as CyaSSL)
 *
 * wolfSSL is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * wolfSSL is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301, USA
 */

#ifndef __ANDROID__
    #include <wolfssl/options.h>
#endif
#include <wolfssl/wolfcrypt/error-crypt.h>
#include <wolfssl/wolfcrypt/md5.h>

#include <com_wolfssl_wolfcrypt_Md5.h>
#include <com_wolfssl_wolfcrypt_WolfCrypt.h>
#include <wolfcrypt_jni_NativeStruct.h>
#include <wolfcrypt_jni_error.h>

/* #define WOLFCRYPT_JNI_DEBUG_ON */
#include <wolfcrypt_jni_debug.h>

JNIEXPORT jlong JNICALL Java_com_wolfssl_wolfcrypt_Md5_mallocNativeStruct(
    JNIEnv* env, jobject this)
{
    jlong ret = 0;

#ifdef NO_MD5
    throwNotCompiledInException(env);
#else

    ret = (jlong) XMALLOC(sizeof(Md5), NULL, DYNAMIC_TYPE_TMP_BUFFER);

    if (!ret)
        throwOutOfMemoryException(env, "Failed to allocate Md5 object");

    LogStr("new Md5() = %p\n", ret);

#endif

    return ret;
}

JNIEXPORT void JNICALL Java_com_wolfssl_wolfcrypt_Md5_initMd5
  (JNIEnv* env, jobject class)
{
#ifndef NO_MD5

    Md5* md5 = (Md5*) getNativeStruct(env, class);

    if (!md5)
        throwWolfCryptExceptionFromError(env, BAD_FUNC_ARG);

    wc_InitMd5(md5);

#else
    throwNotCompiledInException(env);
#endif
}

JNIEXPORT void JNICALL Java_com_wolfssl_wolfcrypt_Md5_md5Update__Ljava_nio_ByteBuffer_2J
  (JNIEnv* env, jobject class, jobject data_buffer, jlong len)
{
#ifndef NO_MD5

    Md5* md5 = (Md5*) getNativeStruct(env, class);
    byte* data = getDirectBufferAddress(env, data_buffer);

    if (!md5 || !data)
        throwWolfCryptExceptionFromError(env, BAD_FUNC_ARG);

    wc_Md5Update(md5, data, len);

    LogStr("wc_Md5Update(md5=%p, data, len)\n", md5);
    LogStr("data[%u]: [%p]\n", (word32)len, data);
    LogHex(data, len);

#else
    throwNotCompiledInException(env);
#endif
}

JNIEXPORT void JNICALL Java_com_wolfssl_wolfcrypt_Md5_md5Update___3BJ
  (JNIEnv* env, jobject class, jbyteArray data_buffer, jlong len)
{
#ifndef NO_MD5

    Md5* md5 = (Md5*) getNativeStruct(env, class);
    byte* data = getByteArray(env, data_buffer);

    if (!md5 || !data)
        throwWolfCryptExceptionFromError(env, BAD_FUNC_ARG);

    wc_Md5Update(md5, data, len);

    LogStr("wc_Md5Update(md5=%p, data, len)\n", md5);
    LogStr("data[%u]: [%p]\n", (word32)len, data);
    LogHex(data, len);

    releaseByteArray(env, data_buffer, data, 1);

#else
    throwNotCompiledInException(env);
#endif
}

JNIEXPORT void JNICALL Java_com_wolfssl_wolfcrypt_Md5_md5Update___3BII
  (JNIEnv* env, jobject class, jbyteArray data_buffer, jint offset,
   jint len)
{
#ifndef NO_MD5

    Md5* md5 = (Md5*) getNativeStruct(env, class);
    byte* data = getByteArray(env, data_buffer);

    if (!md5 || !data || (offset > len))
        throwWolfCryptExceptionFromError(env, BAD_FUNC_ARG);

    wc_Md5Update(md5, data + offset, len);

    LogStr("wc_Md5Update(md5=%p, data, len)\n", md5);
    LogStr("data[%u]: [%p]\n", (word32)len, data + offset);
    LogHex(data + offset, len);

    releaseByteArray(env, data_buffer, data, 0);

#else
    throwNotCompiledInException(env);
#endif
}

JNIEXPORT void JNICALL Java_com_wolfssl_wolfcrypt_Md5_md5Final__Ljava_nio_ByteBuffer_2
  (JNIEnv* env, jobject class, jobject hash_buffer)
{
#ifndef NO_MD5

    Md5* md5 = (Md5*) getNativeStruct(env, class);
    byte* hash = getDirectBufferAddress(env, hash_buffer);

    if (!md5 || !hash)
        throwWolfCryptExceptionFromError(env, BAD_FUNC_ARG);

    wc_Md5Final(md5, hash);

    LogStr("wc_Md5Final(md5=%p, hash)\n", md5);
    LogStr("hash[%u]: [%p]\n", (word32)MD5_DIGEST_SIZE, hash);
    LogHex(hash, MD5_DIGEST_SIZE);

#else
    throwNotCompiledInException(env);
#endif
}

JNIEXPORT void JNICALL Java_com_wolfssl_wolfcrypt_Md5_md5Final___3B
  (JNIEnv* env, jobject class, jbyteArray hash_buffer)
{
#ifndef NO_MD5

    Md5* md5 = (Md5*) getNativeStruct(env, class);
    byte* hash = getByteArray(env, hash_buffer);

    if (!md5 || !hash)
        throwWolfCryptExceptionFromError(env, BAD_FUNC_ARG);

    wc_Md5Final(md5, hash);

    LogStr("wc_Md5Final(md5=%p, hash)\n", md5);
    LogStr("hash[%u]: [%p]\n", (word32)MD5_DIGEST_SIZE, hash);
    LogHex(hash, MD5_DIGEST_SIZE);

    releaseByteArray(env, hash_buffer, hash, 0);

#else
    throwNotCompiledInException(env);
#endif
}

