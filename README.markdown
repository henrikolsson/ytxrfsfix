YouTube Xinerama Fullscreen Fix
=================================================================

The youtube flash player seems to use the width of all of your
xinerama screens combined to calculate the aspect ratio of videos
in full screen mode but since the player is only displayed on one
screen. This is wrong, it will look something like [this][1]

This code fixes it by tricking flash.

Usage:
    $ make
    $ LD_PRELOAD="./ytxrfsfix.so" google-chrome

[1]: http://img192.imageshack.us/img192/8723/youtubefullscreen.png
