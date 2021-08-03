# RandomPasswordGenerator
Wanted a small program to generate myself some random password to be used with a password manager.
Requires a Linux computer with /dev/random

## Compile
```Console
mkdir build
cd build
cmake ..
sudo make install
```

## Usage
```Console
randpwgen -h    # for help
randpwgen       # for generating password of length 16
randpwgen -s 25 # for generating password of length 25
```
