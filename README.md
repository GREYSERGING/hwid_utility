# hwid_utility
hwid_utility - hwid_utility is a small program for viewing, backup and changing hwid.
## Setup
```
git clone https://github.com/GREYSERGING/hwid_utility.git
cd hwid_utility
```

## Building (Only for Windows)
```
gcc hwid.c -o hwid
```

## Using
```
Usage: hwid.exe [-h] [-g] [-b %] [-s %]
  -h | show the current window
  -g | get the hwid of the computer
  -b [to_file] | make a backup of hwid
  -s [new_hwid] | install a new hwid
    Consists of a range of: a-f and 0-9
    Example: "{01234567-89ab-cdef-0123-456789abcdef}"
```

## Example
```
hwid.exe -g
hwid.exe -b hwid.txt
hwid.exe -s {e24a567f-3134-77ae-272a-505a4fbc57d3}
```
