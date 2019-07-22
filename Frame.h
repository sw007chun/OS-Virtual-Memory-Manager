/*
 * Frame.h
 *
 *  Created on: Jul 22, 2019
 *      Author: sungw
 */

#ifndef FRAME_H_
#define FRAME_H_

class Frame {
public:
//	Frame();
//	unsigned is_new:1;
	unsigned frame_num:7;
	unsigned pid:4;
	unsigned v_page_num:6;

};
#endif /* FRAME_H_ */
