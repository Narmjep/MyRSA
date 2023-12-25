# MyRSA
A simple library that defines the encryption methods used in [Encryptor](https://github.com/Narmjep/EncryptorCMDL).

This is a **header only** library. In order to use it, simple copy the .hpp files into your project and add them to your include directory

This project also contains the program [Precalculator](Precalculator) which is used to create a binary data file that contains precalculated numbers used to speed up the key generation process. Simply run 
```bash 
./precalculator
```
 to create the ```data.bin``` cache file and place it in the same directory as ```Ecnryptor.exe```. Optionally you can pass a number as an argument when calling precalculator to specify the range of the numbers to be calculated. 

