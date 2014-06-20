/* Author: Tyler Lee
   head file for 2048
*/
#ifndef __2048_H
#define __2048_H

typedef unsigned short Type;
typedef int ReturnFlag;

/*
 * 4x4 data gram: row start from top to bottom
 *				  col start from left to right
 */
extern Type panel[4][4];
//total score
extern unsigned int score;

//get random number between 0~4
Type getRandomTwoFour();

//add new number: 2 or 4
ReturnFlag addNewNumber();

/* move actions: move in the given direction and then combine the same number,
 * then add a new number of 2 or 4 in spare cell
 *
 * return: if success, return 0; else return 1
 *
 * 'u' -- up
 * 'd' -- down
 * 'l' -- left
 * 'r' -- right
 */
ReturnFlag move(char direction);
ReturnFlag combine(char direction);

ReturnFlag moveCombine(char direction);

/*
 * 2048 game
 */
ReturnFlag showPanel();	// show panel including data
ReturnFlag init_2048();	// initiate data and environment
/*
 * return value: 0 -- success, this will set the score
 *				 1 -- fail
 */
ReturnFlag play_2048();

#endif //__2048_H

