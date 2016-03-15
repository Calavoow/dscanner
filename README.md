# D-Scanner
Dscanner is a tiny program that provides a way for user to d-scan in the fastest way possible.

## How to use
Download the dscanner.ahk file, and install [AutoHotkey](https://autohotkey.com/).
Run the `.ahk` file by double clicking, there should be a green H icon in your taskbar now,
which indicates the script is running.
Keybindings:

* `=`, Increases the search range
* `-`, Decreases the search range
* `+`, Undoes the last `=`/`-` input.
* `_`, Reset to the beginning.

### Example
Warp somewhere with something on d-scan you want to locate.
Open the d-scan and click on the range and perform the reset action (`_`) and press enter.
If the item is still on d-scan, press (`-`) to decrease the search range,
otherwise press (`=`) to increase the search range.
Repeat this process until you have located your target to a sufficient precision.
If you make a mistake, press (`+`) to undo your last (`=`) or (`-`).
Press (`_`) to completely reset and start anew.

## Implementation
The program theory is a simple binary search on the search space of integers in [0-1430],
minor deviations are disregarded.
