#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <iomanip>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/input.h>
#include <unistd.h>
#include "2048.h"

using std::cout;
using std::endl;
using std::setw;

extern Type panel[4][4];
extern unsigned int score;

Type getRandomTwoFour() {
	srand((unsigned int)time(NULL));

	return (Type)(((rand() % 4) / 2 + 1) * 2);
}

ReturnFlag showPanel() {
	system("clear");

	cout<<setw(46)<<"2048 by Tyler Lee"<<endl;
	cout<<setw(50)<<" |-----------------------|"
		<<endl;

	for(int i=0;i<=3;i++)
	{
		cout<<setw(24)<<"";
		for(int j=0;j<=3;j++)
		{
			if(panel[i][j]==0)
				cout<<setw(2)<<"|"<<setw(4)<<" ";
			else
				cout<<setw(2)<<"|"<<setw(4)
					<<panel[i][j];

			if(j==3)
				{
					cout<<setw(2)<<"|"<<endl;
					cout<<setw(50)<<" |-----------------------|"<<endl;
				}
		}
	}
}

ReturnFlag move(char direction) {
	ReturnFlag flag = 1;

	switch(direction) {
		case 'u':	//move up
			for(int j=0; j<4; j++) {
				for(int i=0; i<4; i++) {
					//把数字向该方向集中，即中间没有空格
					if(panel[i][j] != 0) {
						continue;
					}
					else {
						for(int tmp=i+1; tmp<4; tmp++) {
							if(panel[tmp][j] != 0) {
								panel[i][j] = panel[tmp][j];
								panel[tmp][j] = 0;

								//still can move
								flag = 0;

								break;
							}
						}
					}
				}
			}
			break;
		case 'd':	//move down
			for(int j=0; j<4; j++) {
				for(int i=3; i>=0; i--) {
					//把数字向该方向集中，即中间没有空格
					if(panel[i][j] != 0) {
						continue;
					}
					else {
						for(int tmp=i-1; tmp>=0; tmp--) {
							if(panel[tmp][j] != 0) {
								panel[i][j] = panel[tmp][j];
								panel[tmp][j] = 0;

								//still can move
								flag = 0;

								break;
							}
						}
					}
				}
			}
			break;
		case 'l':
			for(int i=0; i<4; i++) {
				for(int j=0; j<4; j++) {
					//把数字向该方向集中，即中间没有空格
					if(panel[i][j] != 0) {
						continue;
					}
					else {
						for(int tmp=j+1; tmp<4; tmp++) {
							if(panel[i][tmp] != 0) {
								panel[i][j] = panel[i][tmp];
								panel[i][tmp] = 0;

								//still can move
								flag = 0;

								break;
							}
						}
					}
				}
			}
			break;
		case 'r':	//move right
			for(int i=0; i<4; i++) {
				for(int j=3; j>=0; j--) {
					//把数字向该方向集中，即中间没有空格
					if(panel[i][j] != 0) {
						continue;
					}
					else {
						for(int tmp=j-1; tmp>=0; tmp--) {
							if(panel[i][tmp] != 0) {
								panel[i][j] = panel[i][tmp];
								panel[i][tmp] = 0;

								//still can move
								flag = 0;

								break;
							}
						}
					}
				}
			}
			break;
		default:
			break;
	}

	return flag;
}

ReturnFlag combine(char direction) {
	ReturnFlag flag = 1;

	switch(direction) {
		case 'u':	//combine up
			for(int j=0; j<4; j++) {
				for(int i=0; i<3; i++) {
					if(panel[i][j]==panel[i+1][j]) {
						panel[i][j] = panel[i][j] + panel[i+1][j];
						panel[i+1][j] = 0;

						//still can move
						flag = 0;
					}
				}
			}
			break;
		case 'd':	//combine down
			for(int j=0; j<4; j++) {
				for(int i=3; i>0; i--) {
					if(panel[i][j]==0 || panel[i][j]==panel[i-1][j]) {
						panel[i][j] = panel[i][j] + panel[i-1][j];
						panel[i-1][j] = 0;

						//still can move
						flag = 0;
					}
				}
			}
			break;
		case 'l':	//combine left
			for(int i=0; i<4; i++) {
				for(int j=0; j<3; j++) {
					if(panel[i][j]==0 || panel[i][j]==panel[i][j+1]) {
						panel[i][j] = panel[i][j] + panel[i][j+1];
						panel[i][j+1] = 0;

						//still can move
						flag = 0;
					}
				}
			}
			break;
		case 'r':	//combine right
			for(int i=0; i<4; i++) {
				for(int j=3; j>0; j--) {
					if(panel[i][j]==0 || panel[i][j]==panel[i][j-1]) {
						panel[i][j] = panel[i][j] + panel[i][j-1];
						panel[i][j-1] = 0;

						//still can move
						flag = 0;
					}
				}
			}
			break;
		default:
			break;
	}

	return flag;
}

/*
 * 应该具备在随机空闲位置产生随机2 4的效果
 */
ReturnFlag addNewNumber() {
	ReturnFlag flag = 1;
	int spare[16];
	for(int i=0; i<16; i++) {
		spare[i] = 0;
	}

	int k = 0;
	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			if(panel[i][j] == 0) {
				spare[k] = 4*i + j;
				k++;
			}
		}
	}

	if(k == 0) {
		perror("panel is full, you lose\n");
		return 1;
	}

	int i = rand() % k;
	int r = spare[i] / 4;
	int c = spare[i] % 4;
	panel[r][c] = getRandomTwoFour();

	flag = 0;

	return flag;
}

ReturnFlag moveCombine(char direction) {
	ReturnFlag flag = 1;

	flag += move(direction);
	flag += combine(direction);
	move(direction);
	/*
	 * 如果有移动或者有合并操作，说明该步骤成功
	 * 反之，如果两步都没有动作，此时flag应该为3，即该步骤失败
	 */
	if(flag < 3) {
		addNewNumber();
		flag = 0;
	}

	return flag;
}


ReturnFlag init_2048() {
	ReturnFlag flag = 1;

	for(int i=0; i<4; i++) {
		for(int j=0; j<4; j++) {
			panel[i][j] = 0;
		}
	}

	srand((unsigned int)time(NULL));
	int i1 = rand() % 4;
	int i2 = (i1 + 1) % 4;
	int j1 = rand() % 4;
	int j2 = (j1 + 1) % 4;

	panel[i1][j1] = 2;
	panel[i2][j2] = 2;

	score = 0;
	flag = 0;

	showPanel();

	return flag;
}


ReturnFlag play_2048() {
	ReturnFlag flag = 0;

	init_2048();	//initiate the data

	int keyboard_fd;
	keyboard_fd = open("/dev/input/event0", O_RDONLY);
	if(keyboard_fd <= 0) {
		perror("open /dev/input/event0 error\n");
		return 1;
	}

	struct input_event i_event;
	while(1) {
		if (read(keyboard_fd, &i_event, sizeof(i_event))
				== sizeof(i_event))
		{
			//key is pressed and then released
			if (i_event.type == EV_KEY && i_event.value == 0) {
				switch(i_event.code) {
					case KEY_UP:
						flag += moveCombine('u');
						showPanel();
						break;
					case KEY_DOWN:
						flag += moveCombine('d');
						showPanel();
						break;
					case KEY_LEFT:
						flag += moveCombine('l');
						showPanel();
						break;
					case KEY_RIGHT:
						flag += moveCombine('r');
						showPanel();
						break;
					default:
						break;
				}
			}
		}
	}
	close(keyboard_fd);

	flag = 0;
	return flag;
}
