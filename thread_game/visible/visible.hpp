//
//  visible.hpp
//  thread_game
//
//  Created by Jin Woong Han on 2017. 4. 16..
//  Copyright © 2017년 skyend. All rights reserved.
//

#ifndef visible_hpp
#define visible_hpp

#include <stdio.h>
#include "../config.h"
#include "../canvas.h"

#endif /* visible_hpp */


class Visible {
public:
    virtual void draw(Canvas *canvas){};
    virtual void tick(double t, double delta){};
};

class Sprite : public Visible {
public:
    double x;
    double y;
    double opacity;
    
    Sprite();
    
    virtual void draw(Canvas *canvas);
    virtual void tick(double t, double delta);
};

