#!/bin/sh


wallpaper=$(ls ~/Pictures/wallpapers | dmenu ) 
[ $wallpaper -z ] || feh --bg-fill /home/kali/Pictures/wallpapers/$wallpaper  
