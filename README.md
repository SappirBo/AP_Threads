# AP_Threads



## Details
The task is to implement a threadpool mechanism and synchronization to parallelize an encryption algorithm in a shared library with two functions: "encode" and "decode". The encryption algorithm is slow and can only handle up to 1024 bytes of data. The CMD TOOL that will use the algorithm above will get its working data from stdIn and put the output to stdOut. The flags "-e" and "-d" will be used for encryption and decryption accordingly. The goal is to utilize multi-threading to improve the algorithm's performance by running it faster on a multi-core system.

## Tests and How to run.
There are some bash scripts for easy testing.<br/>
If your machin doesnt recognize the executable, try `sudo chmod +x test.sh`<br/>
All the tests are included in `test` directory (in all of them give argument 1,2 or 3 for the file you want to test):
* testEncrypt: test for the encryption of a file -> messures the time it takes and print it in the end.
* testDecrypt: test for the decryption of a file -> messures the time it takes and print it in the end.
* testAll: ultimate test for all, given numer [1, 2, 3] as a chosen file, the test will encrypt the file to  `data/tmpResult.txt`, then it will decrypt the file to `data/result.txt`. in the end it will check if the file `data/result.txt` is equals to source file.


## Compare linear run vs thread driven run

File| bytes| encrypt before threadpool|encrypt after threadpool| decrypt before threadpool|decrypt after threadpool
---|---|---|---|---|---
helloWorld.txt| 27 bytes| 0.138 seconds| 0.138 seconds| 0.140 seconds. |0.138 seconds.
az.txt| 2,625 bytes| 13.128 seconds.| 5.124 seconds.|13.139 seconds.|5.129 seconds.
bigFile.txt| 8,571 bytes| 42.858 seconds| 5.242 seconds.|42.898 seconds.|5.196 seconds.


----

before:
1. az.txt, time to encrypt = 13.128seconds. Time taken to decrypt: 13.139 seconds.
2. helloWorld.txt, Time taken to encrypt: 0.138 seconds,Time taken to decrypt: 0.140 seconds.
3. bigFile.txt, Time taken to encrypt: 42.858 seconds, Time taken to decrypt: 42.898 seconds.

after:
1. az.txt, Time taken to encrypt: 2.894 seconds, Time taken to decrypt: 0.017 seconds.
2. helloWorld.txt, Time taken to encrypt: 0.138 seconds, Time taken to decrypt: 0.138 seconds.
3. bigFile.txt, Time taken to encrypt: 1.902 seconds, Time taken to decrypt: 1.947 seconds.

## Sources
[Data about Threadpool and code example](https://nachtimwald.com/2019/04/12/thread-pool-in-c/).

## ToDo
1. adding test script.

