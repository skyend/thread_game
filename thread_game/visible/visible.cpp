//
//  visible.cpp
//  thread_game
//
//  Created by Jin Woong Han on 2017. 4. 16..
//  Copyright © 2017년 skyend. All rights reserved.
//

#include "visible.hpp"
#include <cmath>

#define PI (double)3.14159265

Sprite::Sprite(){
    x = 1;
}

void Sprite::draw(Canvas *can){
    
    for(int x = 0; x < can->width; x++ ){
        double interpolation = (double)x / can->width * 360.0f;
        double t = interpolation * PI / 180.0f;
        double yfector = cos( t );
        double xfector = sin( t + this->x );
        double y =floor(yfector*25);
        double xx = floor(xfector * 25);
        double realY = 30 + y;
        double realX = 30 + xx;
        (*can)(x,realX,(int)rand() * 124);
    }
    
    
    for(int x = 0; x < can->width; x++ ){
        double interpolation = (double)x / can->width * 360.0f;
        double t = interpolation * PI / 180.0f;
        double yfector = cos( t + this->x );
        double xfector = sin( t );
        double y =floor(yfector*25);
        double xx = floor(xfector * 25);
        double realY = 30 + y;
        double realX = 30 + xx;
        (*can)(x,realY,(int)rand() * 124);
    }
    
}


void Sprite::tick(double t, double delta){
    x += delta;
}
