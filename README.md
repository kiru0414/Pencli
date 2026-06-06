# Pencli
It works purely in RAM. No SSD/HDD usage for maximum speed and privacy.

## Installation : Linux / Windows in WSL 

### Prerequisites
- `clang`
- `make`
- `sudo`
- `git`
  
### Build and Install
very easy.
```
$ git clone https://github.com/kiru0414/Pencli
$ cd Pencli
$ make install
```

## Manual
 You can use either `pc` or `pencli`.
 You can use it just like taking notes with a pencil.

Edit memo.
```
$ pencli
```

Change to nano editor.
```
$ export EDITOR=nano
```

Add memo.
```
$ pencli -a "add text"
```

Print memo.
```
$ pencli -p
```

Clear memo.
```
$ pencli -c
```
