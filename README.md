# AP_Threads

URL:  https://github.com/SappirBo/AP_Threads

## Details
The task is to implement a threadpool mechanism and synchronization to parallelize an encryption algorithm in a shared library with two functions: "encode" and "decode". The encryption algorithm is slow and can only handle up to 1024 bytes of data. The CMD TOOL that will use the algorithm above will get its working data from stdIn and put the output to stdOut. The flags "-e" and "-d" will be used for encryption and decryption accordingly. The goal is to utilize multi-threading to improve the algorithm's performance by running it faster on a multi-core system.
<br/>
<br/>
[Full details of the assignment](https://github.com/SappirBo/AP_Threads/blob/main/HW2.pdf).

## How to run.
First of all, use `make` for the main directory (AP_Threads) to create all the executables.<br/>
The coder executable is the executable that we will need and use. <br/> 

You have to way to use `./Coder`:
1. By direct oparte line: `./code <key> <flag> <source> <destination>`
2. By piping file: `cat <source> | ./coder <key> <flag> > <destination>`
Flags:
- `key`: special key for the encrypt/ decrypt, Integer number.
- `flag`: chosen action to preform, `-e` for encrypt, `-d` for decrypt.
- `source`: path to the source file.
- `destination`: path to the destination file.


## Test.
There are some bash scripts for easy testing.<br/>
If your machin doesnt recognize the executable, try `sudo chmod +x test.sh`<br/>
All the tests are included in `test` directory (in all of them give argument 1,2 or 3 for the file you want to test):
* testEncrypt: test for the encryption of a file -> messures the time it takes and print it in the end.
* testDecrypt: test for the decryption of a file -> messures the time it takes and print it in the end.
* testAll: ultimate test for all, given numer [1, 2, 3] as a chosen file, the test will encrypt the file to  `data/tmpResult.txt`, then it will decrypt the file to `data/result.txt`. in the end it will check if the file `data/result.txt` is equals to source file.

![image](https://github.com/SappirBo/AP_Threads/assets/92790326/4f803e27-4fc2-4240-98a6-d00ebce9911e)
![image](https://github.com/SappirBo/AP_Threads/assets/92790326/5040846e-a35d-4d10-8dc9-20f46673762f)

## Compare linear run vs thread driven run

File| bytes| encrypt before threadpool|encrypt after threadpool| decrypt before threadpool|decrypt after threadpool
---|---|---|---|---|---
az.txt| 2,625 bytes| 13.128 seconds.| 5.124 seconds.|13.139 seconds.|5.129 seconds.
helloWorld.txt| 14,499 bytes| 70.917 seconds| 21.165 seconds| 71.475 seconds. |20.485 seconds.
bigFile.txt| 100,999 bytes | 504.968 seconds| 130.608 seconds.|506.004 seconds.|130.490 seconds.


----

data/tmp.txt and data/result.txt are both for testing.

## Sources
1. [Data about Threadpool and code example](https://nachtimwald.com/2019/04/12/thread-pool-in-c/).
2. [youtube: Thread Pools in C](https://www.youtube.com/watch?v=_n2hE2gyPxU&t=459s&ab_channel=CodeVault).
3. [wikipedia: Thread pool](https://en.wikipedia.org/wiki/Thread_pool).
4. [openAi: chatGPT](https://chat.openai.com/).
5. [Full details of the assignment](https://github.com/SappirBo/AP_Threads/blob/main/HW2.pdf).

