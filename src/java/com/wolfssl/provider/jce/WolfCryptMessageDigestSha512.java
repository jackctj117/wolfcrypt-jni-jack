/* WolfCryptMessageDigestSha512.java
 *
 * Copyright (C) 2006-2017 wolfSSL Inc.
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

package com.wolfssl.provider.jce;

import java.util.Arrays;
import java.security.MessageDigestSpi;
import javax.crypto.ShortBufferException;

import com.wolfssl.wolfcrypt.Sha512;

/**
 * wolfCrypt JCE SHA-512 MessageDigest wrapper
 *
 * @author wolfSSL
 * @version 1.0, March 2017
 */
public final class WolfCryptMessageDigestSha512 extends MessageDigestSpi {

    /* internal reference to wolfCrypt JNI Sha object */
    private Sha512 sha;

    public WolfCryptMessageDigestSha512() {

        sha = new Sha512();
        sha.init();
    }

    @Override
    protected byte[] engineDigest() {

        byte[] digest = new byte[Sha512.DIGEST_SIZE];

        try {

            this.sha.digest(digest);

        } catch (ShortBufferException e) {
            throw new RuntimeException(e.getMessage());
        }

        return digest;
    }

    @Override
    protected void engineReset() {

        this.sha.init();
    }

    @Override
    protected void engineUpdate(byte input) {

        byte[] tmp = new byte[1];
        tmp[0] = input;

        this.sha.update(tmp, 1);
    }

    @Override
    protected void engineUpdate(byte[] input, int offset, int len) {

        this.sha.update(input, offset, len);
    }

    @Override
    protected void finalize() throws Throwable {
        try {
            this.sha.releaseNativeStruct();
        } finally {
            super.finalize();
        }
    }
}

