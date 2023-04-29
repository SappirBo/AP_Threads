# AP_Threads


compile with `make`, if you get an error "... libCodec.so: cannot open shared object file: No such file or directory ",<br/>

Set the library search path to include the current directory. You can do this by setting the "LD_LIBRARY_PATH" environment variable to the current directory. Here's how you can do it:
try `export LD_LIBRARY_PATH=.` , 
