# AP_Threads



## Details
The task is to implement a threadpool mechanism and synchronization to parallelize an encryption algorithm in a shared library with two functions: "encode" and "decode". The encryption algorithm is slow and can only handle up to 1024 bytes of data. The CMD TOOL that will use the algorithm above will get its working data from stdIn and put the output to stdOut. The flags "-e" and "-d" will be used for encryption and decryption accordingly. The goal is to utilize multi-threading to improve the algorithm's performance by running it faster on a multi-core system.

## How to run tests.
There are some bash scripts for easy testing.<br/>
If your machin doesnt recognize the executable, try `sudo chmod +x test.sh`<br/>


## Compare linear run vs thread driven run
1. az.txt, time to encrypt = 13.128seconds. Time taken to decrypt: 13.139 seconds.
2. helloWorld.txt, Time taken to encrypt: 0.138 seconds,Time taken to decrypt: 0.140 seconds.
3. bigFile.txt, Time taken to encrypt: 42.858 seconds, Time taken to decrypt: 42.898 seconds.


