
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>

#include <fstream>
#include <string>

#include "windows.h"



using namespace std;
enum {
    SCREEN_WIDTH = 1000,
    SCREEN_HEIGHT = 1400,
    xmove = 27,
    ymove = 27,
    scale = 3,
    rect_size =3
  
};


SDL_Window* win = nullptr;
SDL_Renderer* ren = nullptr;



bool init() {
    bool ok = true;

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
       
    }
    win = SDL_CreateWindow("  ", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (win == nullptr) {   
        ok = false;
    }
    ren = SDL_CreateRenderer(win, -1, SDL_RENDERER_ACCELERATED);
    if (ren == nullptr) {
        ok = false;
    }
    return ok;
}



void quit() {
    SDL_DestroyWindow(win);
    win = NULL;
    SDL_DestroyRenderer(ren);
    ren = NULL;

    SDL_Quit;
}


class nodes {
public:
    int x;
    int y;
    int down;
    int right;
    int gx;
    int gy;
    bool exist;

    nodes()
    {
        x = 0;
        y = 0;
        down=-1;
        right=-1;
        gx = 0;
        gy = 0;
        exist = false;
    }

    nodes(int x_, int y_,int down_, int right_) 
    {
        x = x_;
        y = y_;
        down = down_;
        right = right_;
        gx = 0;
        gy = 0;
        exist = true;
    }


    

    
};

void drawright(nodes*node, int grid[][100], int mainnode, int r) {

    node[r].x = node[mainnode].x + xmove + 3;
    node[r].y = node[mainnode].y;

    SDL_SetRenderDrawColor(ren, 230, 230, 250, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderDrawLine(ren, node[mainnode].x + 3, node[mainnode].y + 1, node[r].x, node[r].y + 1);


    SDL_Rect rect = { node[r].x, node[r].y , rect_size, rect_size };
    SDL_SetRenderDrawColor(ren, 220, 20, 60, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderFillRect(ren, &rect);
    node[mainnode].right = r;

    node[r].gx = node[mainnode].gx + 1;
    node[r].gy = node[mainnode].gy;
    int x = node[r].gx;
    int y = node[r].gy;
    grid[x][y] = 1;
}

void drawdown(nodes* node, int grid[][100], int mainnode, int d) {

    node[d].x = node[mainnode].x ;
    node[d].y = node[mainnode].y + ymove + 3;

    SDL_SetRenderDrawColor(ren, 230, 230, 250, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderDrawLine(ren, node[mainnode].x + 1, node[mainnode].y + 3, node[d].x+1, node[d].y);


    SDL_Rect rect = { node[d].x, node[d].y , rect_size, rect_size };
    SDL_SetRenderDrawColor(ren, 220, 20, 60, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderFillRect(ren, &rect);
    node[mainnode].down = d;

    node[d].gx = node[mainnode].gx;
    node[d].gy = node[mainnode].gy+1;
    int x = node[d].gx;
    int y = node[d].gy;
    grid[x][y] = 1;
}

void drowdown_(nodes* node, int grid[][100], int i,int n, int c) {


    
   
    node[i+c] = nodes();
    node[i + c].x = node[i].x;
    node[i + c].y = node[i].y + ymove + 3;

    SDL_SetRenderDrawColor(ren, 173, 255, 47, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderDrawLine(ren, node[i].x + 1, node[i].y + 3, node[ i+ c].x + 1, node[ i + c].y);


    SDL_Rect rect = { node[i +  c].x, node[ i +  c].y , 3, 3 };
   
    SDL_SetRenderDrawColor(ren, 220, 20, 60, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderFillRect(ren, &rect);
    node[i+1].right = i+1;

    node[ i +  c].gx = node[i].gx;
    node[ i +  c].gy = node[i].gy + 1;
    grid[node[i+c].gx][node[i+ c].gy] = 1;


    SDL_SetRenderDrawColor(ren, 220, 20, 60, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderFillRect(ren, &rect);
}

void drowright_(nodes* node, int grid[][100], int i,int n,int c) {
    

    
    node[i + 1 + c] = nodes();
    node[i + 1 + c].x = node[i].x + xmove + 3;
    node[i + 1 + c].y = node[i].y;

    SDL_SetRenderDrawColor(ren, 173, 255, 47, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderDrawLine(ren, node[i].x + 3, node[i].y + 1, node[i + 1 + c].x, node[i + 1 + c].y + 1);



    SDL_Rect rect = { node[i + 1 + c].x, node[i + 1 + c].y , rect_size, rect_size };
    SDL_SetRenderDrawColor(ren, 220, 20, 60, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderFillRect(ren, &rect);
    node[i].right =  i;

    node[i + 1 + c].gx = node[i].gx + 1;
    node[ i + 1 + c].gy = node[i].gy;
    grid[node[i + 1 + c].gx][node[i + 1 + c].gy] = 1;



    SDL_SetRenderDrawColor(ren, 220, 20, 60, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderFillRect(ren, &rect);
}



int main(int argc, char* argv[]) {

    string path =  "C:\\graph4.txt";

    if (!init()) {
        quit();
        return 1;
    }

    SDL_SetRenderDrawColor(ren, 0x00, 0x00, 0x00, 0x00);// green
    SDL_RenderClear(ren);
    SDL_SetRenderDrawColor(ren, 173, 255, 47, 0); // black
    

    
    int x0 = 10;
    int y0 = 10;
    int x;
    int n ;
    int buf;
    int mainnode;
    int r;
    int d;
    

    int grid[100][100];
    memset(grid, 0,sizeof(grid)/4);

    

    SDL_Rect rect = { x0, y0, rect_size, rect_size };
    SDL_SetRenderDrawColor(ren, 220, 20, 60, 0);
    SDL_RenderSetScale(ren, scale, scale);
    SDL_RenderFillRect(ren, &rect);

    
    std::ifstream in(path); 
    
       
    in >> n;
    nodes* node = new nodes[n+1];

     while (!in.eof()) 
     {

      in >> mainnode;
      in >> r;
      in >> d;

                 
      if (mainnode == 1) 
      {
         node[mainnode].x = x0;
         node[mainnode].y = y0;
         grid[0][0] = 1;
         node[1].gx = 0;
         node[1].gy = 0;
      }
                    
                   
      if (r != 0) 
      {
        if (grid[node[mainnode].gx+1][node[mainnode].gy] == 0) 
        {
            drawright(node, grid, mainnode, r);
        }
      }

                   
      if (d != 0)
      {
        if (grid[node[mainnode].gx ][node[mainnode].gy+1] == 0)
        {
           drawdown(node, grid, mainnode, d);
        }               
      }
                                  
     }
           
           
    in.close();     

    int count = 1000;
    int k = count*n;
    int c = 1;
    int iter = k / n;
    nodes* node_ = new nodes[k];
        

    for (int i = 1; i < n+1; i++)
    {
       node_[i].x = node[i].x;
       node_[i].y = node[i].y;
       node_[i].gx = node[i].gx;
       node_[i].gy = node[i].gy;
       node_[i].right = node[i].right;
       node_[i].down = node[i].down;
       node_[i].exist = node[i].exist;
    }
    delete[] node;

       
        
    for (int i = 1; i <0; i++) 
    {        
       if (grid[node_[i].gx + 1][node_[i].gy] != 1) 
       { 
           if (node_[i].exist == true)
           {
               c = c - 1;
           }
          drowright_(node_, grid, i,n,c);              
       }
            
       if (grid[node_[i].gx][node_[i].gy+1] != 1) 
       {
        if (node_[i].exist == true)
        {
           c = c - 1;
        }
        drowdown_(node_, grid, i,n,c);
               
       }
          c++;
    }

    SDL_RenderPresent(ren);
    SDL_Delay(50000000);
    delete[] node_;
    quit();
    return 0;
}
