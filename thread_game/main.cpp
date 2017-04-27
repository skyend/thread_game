//
//  main.cpp
//  thread_game
//
//  Created by Jin Woong Han on 2017. 4. 15..
//  Copyright © 2017년 skyend. All rights reserved.
//

#include <iostream>
#include <mutex>
#include <thread>
#include <vector>
#include <ncurses.h>
#include <unistd.h>
#include <signal.h>
#include <ctime>
#include <chrono>

#include "./config.h"
#include "./canvas.h"
#include "./visible/visible.hpp"


void tickThread();
void drawThread(Canvas * canvas);

std::mutex mapMutex;
std::vector<Visible*> visibleList;
clock_t lastDrawTime = 0;
clock_t lastTickTime = 0;

void sig_handler(int signo){
     printf("\nSIG %d \n", signo);
    
    if( signo == 2){
        endwin();
    }
    
    exit(1);
}

int main(int argc, const char * argv[]) {
    if( signal(SIGINT, sig_handler) == SIG_ERR)
        printf("\ncan't catch SIGKILL\n");
    
    initscr();
    noecho();
    curs_set(FALSE);
    
    Canvas * canvas = new Canvas(screenWidth,screenHeight);
    
    Sprite sprite{};
    
    visibleList.push_back(&sprite);
    
    std::thread drawProc{ drawThread, canvas};
    std::thread runProc{ tickThread };
    
    drawProc.join();
    runProc.join();
    
    
    endwin();
    return 0;
}


void drawThread(Canvas * canvas){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_sec;
    while(FOREVER){
        std::vector<char> charVec;
        
        std::unique_lock<std::mutex> lck{mapMutex};
        
        clear();
        
        
        canvas->clear();
        // draw to canvas
        for( auto v : visibleList ){
            v->draw(canvas);
        }
        
        int dotCount = 0;
        // rendering
        for( int y = 0; y < canvas->height ; y++ ){
            for( int x = 0; x < canvas->width; x++ ){
                
                int index = ( canvas->width * y ) + x;
                Pixel *px = canvas->map[index];
                
                mvprintw(y, x, &px->character);
                
                if( px->character == 'c'){
                    dotCount ++;
                }
            }
        }
        
        start = std::chrono::system_clock::now();
        elapsed_sec = start - end;
        mvprintw(0, 0, "FPS:%f \nprintCount:%d",  double(1 / elapsed_sec.count()), dotCount);
        end = std::chrono::system_clock::now();
        
        
        lck.unlock();
        
        refresh();
        usleep(DELAY);
        
    }
}

void tickThread(){
    std::chrono::time_point<std::chrono::system_clock> start, end;
    std::chrono::duration<double> elapsed_sec;
    
    while(FOREVER){
        std::unique_lock<std::mutex> lck{mapMutex};
        start = std::chrono::system_clock::now();
        
        
        for( auto v : visibleList ){
            v->tick(0,elapsed_sec.count());
        }
        
        
        elapsed_sec = start - end;
        end = std::chrono::system_clock::now();
        lck.unlock();
        usleep(DELAY);
        
        lastTickTime = clock();
    }
}
