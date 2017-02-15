[![Android Arsenal](https://img.shields.io/badge/Android%20Arsenal-RNCryptorNative-green.svg?style=true)](https://android-arsenal.com/details/1/3643)

## RNCryptorNative

Android JNI model implementation of Rob Napier's RNCryptor.


#### Usage

  ```java
  
RNCryptorNative rncryptor = new RNCryptorNative();

byte[] encrypted = rncryptor.encrypt(raw, password);

byte[] decrypted = rncryptor.decrypt(encrypted, password)

//Working with files

//Encrypt

RNCryptorNative.encryptFile(new File("path/to/original"), new File("path/to/encrypted"), "password");

//Decrypt

RNCryptorNative.decryptFile(new File("path/to/encrypted"), new File("path/to/decrypted"), "password");
  ```
  
#### Benchmark:

You might know that JNCryptor (Java port for RNCryptor) already exists. But there is a huge problem - performance. This is why RNCryptorNative is better solution. Screenshots of benchmarks: 

| <img src="screenshots/1.png" width="250"/> | <img src="screenshots/25.png" width="250"/> |
  
## Credits

[Rob Napier](https://github.com/rnapier), [RNCryptor Team](https://github.com/RNCryptor), [MPAndroidChart](https://github.com/PhilJay/MPAndroidChart)
