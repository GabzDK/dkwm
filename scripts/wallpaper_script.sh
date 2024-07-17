#!/bin/sh


wallpaper=$(ls ~/Pictures/wallpapers | rofi -dmenu -i -l 10 ) 
[ $wallpaper -z ] || feh --bg-fill /home/kali/Pictures/wallpapers/$wallpaper  
