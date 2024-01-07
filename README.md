# Pascha GUI
Pascha GUI is a simple GUI program to calculate and display the date of Pascha (Easter).

## Installation

``` sh
git clone https://gitlab.com/cmmescher/pascha-gui
cd pascha-gui
cmake -S . -B build
cmake --build build
cmake --install build
```

alternatively run the following to not use system wxwidgets and/or fmt libraries:

```sh
cmake -S . -B build -DCMAKE_BUILD_TYPE=Release -DUSE_SYSTEM_WX=OFF -DUSE_SYSTEM_FMT=OFF
```

For users of **Arch**-based distributions, Pascha GUI is available on the AUR as [pascha-gui-git](https://aur.archlinux.org/packages/pascha-gui-git) or [pascha-gui-bin](https://aur.archlinux.org/packages/pascha-gui-bin).

You can cross-compile for Windows on a GNU+Linux system using mingw and the following commands:
```sh
cmake -S . -B buildwin -DCMAKE_TOOLCHAIN_FILE=tc-mingw.cmake -DUSE_SYSTEM_FMT=OFF -DUSE_SYSTEM_WX=OFF
cmake --build buildwin
```

## Uninstallation

From within the `pascha-gui` git directory run:

```sh
cmake --build build --target uninstall
```

## Dependencies

- `wxwidgets` -- GUI API.
- `fmt` -- C++ formatting library.

## Usage

`pascha-gui` runs the graphical program. The calculation method, target output date, output calendar, input year, and other options can all be specified in the graphical interface.

Persistent settings are also available to specify the name used for Pascha (or Easter), the date format, and date separator.

## Compatibility

Pascha GUI has been tested on GNU+Linux, FreeBSD, OpenBSD, and Windows systems. It may work on MacOS or others, but it may not. If you do get it to run on
any of these, please let me know, so this can be updated.

## Version

- v1.0
First released publicly on the O.S. Feast of the Nativity 7532 (2023) (January 7, 2024 N.S.).

## Author

Written by Christopher Michael Mescher originally in 2022.

## Copyright and License

Copyright © 2022, 2024 Christopher Michael Mescher.

License [GPLv3+](https://gnu.org/licenses/gpl.html).

## Project status

The project is mostly complete. No new features are planned, but bugs can be
reported to `echo \<pascha-mescher+faith\>|sed s/\+/./g\;s/\-/@/` and they will
be worked on.

## Changelog
