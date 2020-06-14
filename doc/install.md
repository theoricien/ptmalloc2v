# Installation of the ptmalloc2v library

This will teach you how to install properly the ptmalloc2v library with ready-to-use commands

## Support

ptmalloc2v is only available for GNU/Linux OS. I can't guarantee the well work of it on any other support.

## Prerequisite

You need to have GCC for 64 and/or 32  bits with libc Debug Mode. So make sure you have these, else, just follow this command
```Bash
make install
```
Or, if you want to do it by hand
```Bash
sudo apt-get install -y update
sudo apt-get install -y build-essential libc-dbg:i386 libc-dbg:adm64 gcc-multilib
```

## Installation

To install the ptmalloc2v library, you just need to do this command
```Bash
make
```
If it does'nt compile well, you can also modify the `Makefile` file in the root project directory. But it technically sould'nt happen.  
After this, you'll have your library ready to be used.  
You can config however your want, like put in the `/usr/include` folder the `include/` ptmalloc2v files or import them themselves in your project.  
```Bash
# (Optional)
sudo mkdir /usr/include/ptm2v/
sudo mv include/* /usr/include/ptm2v/*
```
So in your project you'll just have this little include:
```C
#include <ptm2v/libptm2v.h>
```
The `.a`/`libptm2v.a` file is in the `libs/` directory

## Project Usage

So now that you can include your files, you need to also link the static library file.  
I will not show you how to use GCC but, you can put this `.a` file into your standard library path (like `/usr/local/lib`) for easier usage.