# AP_Threads


compile with `make`, if you get an error "... libCodec.so: cannot open shared object file: No such file or directory ",<br/>

Set the library search path to include the current directory. You can do this by setting the "LD_LIBRARY_PATH" environment variable to the current directory. Here's how you can do it:
try `export LD_LIBRARY_PATH=.` , 


## Details
The task is to implement a threadpool mechanism and synchronization to parallelize an encryption algorithm in a shared library with two functions: "encode" and "decode". The encryption algorithm is slow and can only handle up to 1024 bytes of data. The CMD TOOL that will use the algorithm above will get its working data from stdIn and put the output to stdOut. The flags "-e" and "-d" will be used for encryption and decryption accordingly. The goal is to utilize multi-threading to improve the algorithm's performance by running it faster on a multi-core system.
