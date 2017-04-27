//
//  canvas.h
//  thread_game
//
//  Created by Jin Woong Han on 2017. 4. 16..
//  Copyright © 2017년 skyend. All rights reserved.
//

#ifndef canvas_h
#define canvas_h
#include <cstdlib>


struct Pixel {
    char character;
    int color;
};

class Canvas {
public:
    int width;
    int height;
    
    Pixel **map;
    
    Canvas(int screenWidth,int screenHeight):width(screenWidth), height(screenHeight) {
        map = (Pixel**)malloc( sizeof(Pixel*) * width * height );
        
        for(int i = 0; i < width*height; i++ ){
            (*(map + i)) = new Pixel{.character = '\0'};
        }
    };
    
    void operator()(int x, int y, char c, long colorCode = 0){
        // x 또는 y 가 넓이, 높이를 초과하면 그리지 않는다.
        if( x < width && y < height && x >= 0 && y >= 0 ){
            int spreadedCoordination = y * width + x;
        
            (map[spreadedCoordination])->character = c;
        }
    };
    
    void clear(){
        for(int i = 0; i < width*height; i++ ){
            (*(map + i))->character = ' ';
        }
    }
    
    ~Canvas(){
        for(int i = 0; i < width*height; i++ ){
            free(*(map + i));
        }
        
        free(map);
    }
};

#endif /* canvas_h */

