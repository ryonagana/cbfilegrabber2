# cbfilegrabber2
File packer for my games still beta

## Usage

cbfilegrabber2 --zip myassets.dat --file  myassets.png

# or

cbfilegrabber2 --package myassets.dat --file  myassets.png


## Miniz by richgel999
miniz.c 2.2.0 - public domain deflate/inflate, zlib-subset, ZIP reading/writing/appending, PNG writing
See "unlicense" statement at the end of this file.
Rich Geldreich <richgel99@gmail.com>, last updated Oct. 13, 2013
Implements RFC 1950: http://www.ietf.org/rfc/rfc1950.txt and RFC 1951: http://www.ietf.org/rfc/rfc1951.txt


## .BAT example
```console
@echo off

cbfilegrabber2.exe --package assets.dat --file assets\bt.png
cbfilegrabber2.exe --package assets.dat --file assets\flag_blue.bmp
cbfilegrabber2.exe --package assets.dat --file assets\flag_red.bmp
cbfilegrabber2.exe --package assets.dat --file assets\main.map
cbfilegrabber2.exe --package assets.dat --file assets\newbie_ski.bmp
cbfilegrabber2.exe --package assets.dat --file assets\ski1.bmp
cbfilegrabber2.exe --package assets.dat --file assets\snowman.bmp
PAUSE

```

## .sh example
```console
#!/bin/bash
cbfilegrabber2 --package assets.dat --file assets/bt.png
cbfilegrabber2 --package assets.dat --file assets/flag_blue.bmp
cbfilegrabber2 --package assets.dat --file assets/flag_red.bmp
cbfilegrabber2 --package assets.dat --file assets\main.map
cbfilegrabber2 --package assets.dat --file assets/newbie_ski.bmp
cbfilegrabber2 --package assets.dat --file assets/ski1.bmp
cbfilegrabber2 --package assets.dat --file assets/snowman.bmp

```
