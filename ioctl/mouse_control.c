#include<stdio.h>
#include<linux/input.h>
#include<unistd.h>
#include<fcntl.h>
#include<sys/stat.h>

int main() {
	int mouse_fd;
	struct input_event i_event;

	mouse_fd = open("/dev/input/event13", O_RDONLY);
	if(mouse_fd <= 0) {
		perror("open /dev/input/event13 error\n");
		return 1;
	}

	while(1) {
		if (read(mouse_fd, &i_event, sizeof(i_event))
				== sizeof(i_event))
		{
			if (i_event.type == EV_KEY)
				if (i_event.value == 0 || i_event.value == 1)
					printf("key\t%d\t%s\n", i_event.code,
						(i_event.value) ? "Pressed" : "Released");
				//if(i_event.code==KEY_ESC)
				//	break;
				if(i_event.code==BTN_LEFT)
					printf("mouse left button click\n");
				if(i_event.code==BTN_RIGHT)
					printf("mouse right button click\n");
		}
	}

	close(mouse_fd);

	return 0;
}
