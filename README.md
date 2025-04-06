this code generates an image of the windows logo in ASCII hihi

this will be my last project using windows11 from now on i will program using linux im still thinking about which distribution to use but everything will be fine

thinking about it now this project could be a humble gift to Microsoft for its 50th anniversary <3

## how to use

```bash
git clone https://github.com/ppp16bit/win
cd the repository
```

## essentials

- **windows 10 or 11**
- **g++ with Win32 API support** (MinGW recommended)

you can use:

- [MSYS2](https://www.msys2.org/) (recommended)
- [MinGW-w64 standalone](https://winlibs.com/)
- [TDM-GCC](https://jmeubank.github.io/tdm-gcc/)

## how to compile 

Se você estiver usando o **g++** com suporte a Win32 (como no MinGW):

``bash
g++ -o winn.exe win.cpp -mwindows
``

``bash
./win.exe
``
>`-mwindows` avoids opening a terminal along with the window.

a window will open with the ASCII art rendered in **white text on a black background** 🖤

obligatory screenshot

![screenshot](preview.png)