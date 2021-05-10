#!/usr/bin/env bash

log stream | awk '
                    /Post event kCameraStreamStart/  { system("mqtt pub -i laptop  -p 1883 --topic sensor/camera/laptop -h 192.168.1.100 -u mqtt -p broker --message \"{ \\\"onair\\\": 1 }\"") }
                    /Post event kCameraStreamStop/   { system("mqtt pub -i laptop  -p 1883 --topic sensor/camera/laptop -h 192.168.1.100 -u mqtt -p broker --message \"{ \\\"onair\\\": 0 }\"") }'
