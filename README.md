# AP_Threads



## Details
The task is to implement a threadpool mechanism and synchronization to parallelize an encryption algorithm in a shared library with two functions: "encode" and "decode". The encryption algorithm is slow and can only handle up to 1024 bytes of data. The CMD TOOL that will use the algorithm above will get its working data from stdIn and put the output to stdOut. The flags "-e" and "-d" will be used for encryption and decryption accordingly. The goal is to utilize multi-threading to improve the algorithm's performance by running it faster on a multi-core system.

## How to run tests.
There are some bash scripts for easy testing.<br/>
If your machin doesnt recognize the executable, try `sudo chmod +x test.sh`<br/>


## Compare linear run vs thread driven run

File| bytes| encrypt before threadpool|encrypt after threadpool| decrypt before threadpool|decrypt after threadpool
---|---|---|---|---|---
helloWorld.txt| 27 bytes| 0.138 seconds| 0.138 seconds| 0.140 seconds. |0.138 seconds.
az.txt| 2,625 bytes| 13.128seconds.| 2.894 seconds.|13.139 seconds.|0.017 seconds.
bigFile.txt| 8,571 bytes| 42.858 seconds| 1.902 seconds.|42.898 seconds.|1.947 seconds.

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
1. check validation of "<" Operator.
2. adding test script.

