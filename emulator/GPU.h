#pragma once
#include "Memory.h"
#include <cstdio>
struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class GPU {
public:
    // 128^2 = 16384 = 0x4000 wor
    static constexpr int WIDTH = 128; 
    static constexpr int HEIGHT = 128;
    static constexpr int PIXEL_COUNT = WIDTH*HEIGHT;

    const uint16_t* getBuffer() {return buffer_;}
    explicit GPU(int scale = 4);
    ~GPU();

    bool init();

    void pollEvents();
    bool shouldQuit();
    bool pause = false;
    bool step = false;
    bool restart = false;

    void drawFrame(Memory* memory);
    void present(uint16_t* pixels);

    static uint16_t rgb555(uint8_t r, uint8_t g, uint8_t b);
    
    static void test(uint16_t* out);
private:
    int scale_;
    bool sdlReady_;
    bool quit_;

    SDL_Window* window_;
    SDL_Renderer* renderer_;
    SDL_Texture* texture_;

    uint16_t buffer_[PIXEL_COUNT]; // yes
                                   
    GPU(const GPU&) = delete; // shit
    GPU& operator=(const GPU&) = delete;
};
