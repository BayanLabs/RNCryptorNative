package tgio.rncryptor;

import java.io.BufferedInputStream;
import java.io.BufferedOutputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.FileNotFoundException;
import java.io.FileOutputStream;
import java.io.IOException;

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
public class RNCryptorNative {

    static {
        System.loadLibrary("gnustl_shared");
        System.loadLibrary("cryptopp_shared");
        System.loadLibrary("rncrypto");
    }

    /**
     * @return device architecture type
     */
    public native String getABI();

    /**
     * Encrypts raw binary data.
     * @param raw just raw binary data
     * @param password strong generated password
     * @return encrypted data
     */
    public native byte[] encrypt(byte[] raw, String password);

    /**
     * Decrypts encrypted binary data.
     * @param encrypted encrypted binary data
     * @param password strong generated password
     * @return decrypted raw data
     */
    public native byte[] decrypt(byte[] encrypted, String password);

    /**
     * Encrypts file using password
     * @param raw the original file to be encrypted
     * @param encryptedFile the result file
     * @param password strong generated password
     * @throws IOException
     */
    public static void encryptFile(File raw, File encryptedFile, String password) throws IOException {
        byte[] data = readBytes(raw);
        byte[] encryptedBytes = new RNCryptorNative().encrypt(data, password);
        writeBytes(encryptedFile, encryptedBytes);
    }

    /**
     * Decrypts file using password
     * @param encryptedFile file which needs to be decrypted
     * @param result destination file for decrypted file
     * @param password strong generated password
     * @throws IOException
     */
    public static void decryptFile(File encryptedFile, File result, String password) throws IOException {
        byte[] data = readBytes(encryptedFile);
        byte[] decryptedData = new RNCryptorNative().decrypt(data, password);
        writeBytes(result, decryptedData);
    }


    private static byte[] readBytes(File file){
        int size = (int) file.length();
        byte[] bytes = new byte[size];
        try {
            BufferedInputStream buf = new BufferedInputStream(new FileInputStream(file));
            buf.read(bytes, 0, bytes.length);
            buf.close();
        } catch (FileNotFoundException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        } catch (IOException e) {
            // TODO Auto-generated catch block
            e.printStackTrace();
        }
        return bytes;
    }

    private static void writeBytes(File file, byte[] bytes) throws IOException{
        BufferedOutputStream bos = new BufferedOutputStream(new FileOutputStream(file));
        bos.write(bytes);
        bos.flush();
        bos.close();
    }
}
