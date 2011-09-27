/*
 * Ball.h
 *
 *  Created on: Nov 27, 2010
 *      Author: ross
 */

#ifndef BALL_H_
#define BALL_H_

class Ball {
public:
    Ball();
    virtual ~Ball();

    float x;
    float y;
    int diameter;
    float velocity;
    float direction;
};

#endif /* BALL_H_ */
