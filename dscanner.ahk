#ifWinActive EVE
initiateVariables()

-::
	; -
	prevRange := range
	range := round(range - step, 2)
	step := max(step/2, 0.01) ; lower bound by 0.01 au

	scanRange(range)
Return

=::
	; =
	prevRange := range
	range := round(range + step, 2)
	step := max(step/2, 0.01) ; lower bound by 0.01 au
	scanRange(range)
Return

+=::
	; +
	range := prevRange
	step := step * 2
	scanRange(range)
Return

+-::
	; _
	initiateVariables()
	scanRange(range)
Return

scanRange(range) {
	clipboard = %range%
	Send ^a ; Overwrite previous distance
	Send ^v
}

initiateVariables() {
	global
	range := round(14.30/2, 2)
	prevRange := range
	step := range/2
}

max(first, second) {
	return first > second? first : second
}