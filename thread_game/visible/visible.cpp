//
//  visible.cpp
//  thread_game
//
//  Created by Jin Woong Han on 2017. 4. 16..
//  Copyright © 2017년 skyend. All rights reserved.
//

#include "visible.hpp"



Sprite::Sprite(){
    
}

void Sprite::draw(Canvas *can){
    (*can)(10,20,'c');
}


void Sprite::tick(double t, double delta){
    
}
