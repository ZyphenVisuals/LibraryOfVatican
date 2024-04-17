# Disclaimer

This is a university assignment for the West University of Timisoara. Code might be (memory) unsafe.

# Building

## Requirements

This program relies on Linux libraries to work.

Additionally, any dependencies required for compiling with `ncursrs.h`, `menu.h`, `form.h` and `openssl` must be installed.
For Arch linux (though both should be installed by default as dependencies of `coreutils`):

```sh
sudo pacman -S ncurses openssl
```

## Compiling

Compiling is done with the following command:

```sh
gcc main.c include/* -lssl -lcrypto -lncurses -lmenu -lform -o lov
```

Replacing `gcc` with `clang` should also work as a drop-in replacement with no extra changes.

# Usage

## Creating your user

Register a user by calling:

```sh
./lov register [surname] [name]
```

You will be prompted to enter and confirm your password, which is stored in hashed form.

## Using the app

Log in by typing:

```sh
./lov login [surname] [name]
```

After confirming your password, you will enter the guided `ncurses` menus.
