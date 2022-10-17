#!/bin/bash

#watch -ptn 0 "xdotool getwindowfocus | xargs -I{} echo WindowId: {} && xdotool getwindowfocus | xargs xprop -id | grep -E \"PID|WM_NAME\""

xdotool getwindowfocus | xargs -I{} echo WindowId: {} &&
xdotool getwindowfocus | xargs xprop -id | grep -E "PID|WM_NAME"
