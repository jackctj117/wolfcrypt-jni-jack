/* WolfCryptMessageDigestSha512.java
 *
 * Copyright (C) 2006-2025 wolfSSL Inc.
 *
 * This file is part of wolfSSL.
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
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1335, USA
 */

package com.wolfssl.provider.jce;

import java.security.MessageDigestSpi;
import javax.crypto.ShortBufferException;

import com.wolfssl.wolfcrypt.Sha512;

/**
 * wolfCrypt JCE SHA2-512 MessageDigest wrapper
 */
public final class WolfCryptMessageDigestSha512
    extends MessageDigestSpi implements Cloneable {

    /* internal reference to wolfCrypt JNI Sha object */
    private Sha512 sha;

    /**
     * Create new WolfCryptMessageDigestSha512 object
     */
    public WolfCryptMessageDigestSha512() {

        sha = new Sha512();
        sha.init();
    }

    /**
     * Create new WolfCryptMessageDigestSha512 based on existing Sha512 object.
     * Existing object should already be initialized.
     *
     * @param sha initialized Sha512 object to be used with this MessageDigest
     */
    private WolfCryptMessageDigestSha512(Sha512 sha) {
        this.sha = sha;
    }

    @Override
    protected byte[] engineDigest() {

        byte[] digest = new byte[Sha512.DIGEST_SIZE];

        try {

            this.sha.digest(digest);

        } catch (ShortBufferException e) {
            throw new RuntimeException(e.getMessage());
        }

        log("generated final digest, len: " + digest.length);

        return digest;
    }

    @Override
    protected void engineReset() {

        this.sha.init();

        log("engine reset");
    }

    @Override
    protected void engineUpdate(byte input) {

        byte[] tmp = new byte[1];
        tmp[0] = input;

        this.sha.update(tmp, 1);

        log("update with single byte");
    }

    @Override
    protected void engineUpdate(byte[] input, int offset, int len) {

        this.sha.update(input, offset, len);

        log("update, offset: " + offset + ", len: " + len);
    }

    @Override
    protected int engineGetDigestLength() {
        return this.sha.digestSize();
    }

    private void log(String msg) {
        WolfCryptDebug.log(getClass(), WolfCryptDebug.INFO,
            () -> "[SHA512] " + msg);
    }

    @Override
    public Object clone() {
        Sha512 shaCopy = (Sha512)this.sha.clone();
        return new WolfCryptMessageDigestSha512(shaCopy);
    }

    @SuppressWarnings("deprecation")
    @Override
    protected void finalize() throws Throwable {
        try {
            if (this.sha != null)
                this.sha.releaseNativeStruct();
        } finally {
            super.finalize();
        }
    }
}

