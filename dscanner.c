#include <linux/input.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <stdbool.h>

#define START_RANGE (1430 / 2)
#define START_STEP (START_RANGE/2)

int main(int argc, char **argv)
{
	int fd;
	if(argc < 2) {
		printf("usage: %s <device>\n", argv[0]);
		return 1;
	}
	printf("Using %s\n", argv[1]);
	fd = open(argv[1], O_RDONLY);
	struct input_event ev;

	bool shiftpressed = false;
	bool firstPlus = false;
	int searchRange = START_RANGE;
	int prevRange = START_RANGE;
	int step = START_STEP;

	printf("Starting main loop\n");
	while (1)
	{
		read(fd, &ev, sizeof(struct input_event));
		/**
		 * Listen only to keyup for plus and minus and equals.
		 *
		 * To detect + we also need to remember the shift state.
		 **/
		if(ev.type == EV_KEY) {
			printf("Key event value %d", ev.value);
			if(ev.code == 42) {
				shiftpressed = ev.value == 1 || ev.value == 2;
			} else if( ev.value == 1 ) {
				if( ev.code == 12 ) {
					prevRange = searchRange;
					searchRange -= step;
					step /= 2;
					firstPlus = false;
				} else if( ev.code == 13 ) {
					if(shiftpressed) {
						// ++
						if(firstPlus) {
							searchRange = START_RANGE;
							prevRange = START_RANGE;
							step = START_STEP;
							printf("Resetting search range\n");
						} else {
							// +
							firstPlus = true;
							// Reset range to prev, in case of mistake
							searchRange = prevRange;
							step *= 2;
						}
					} else {
						// =
						prevRange = searchRange;
						searchRange += step;
						step /= 2;
					}
				}
			}
			printf("Search range %d\n", searchRange);
		}
		printf("key %i state %i\n", ev.code, ev.value);
	}
}
