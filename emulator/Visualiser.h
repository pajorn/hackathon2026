#pragma once
#include <cstdint>
#include "Memory.h"
#include "Registers.h"

struct SDL_Window;
struct SDL_Renderer;
struct SDL_Texture;

class Visualiser {
public:
    static const int W = 512;
    static const int H = 384;
    static const int GP_COUNT = 16; // !!!!!DO NOT TOUCHh
    

    explicit Visualiser(int scale = 2);
    ~Visualiser();
    bool init();
    void draw(Registers& reg, Memory& mem, bool paused);

private:
    void drawRegisters(Registers& reg);
    void drawStack(Registers& reg, Memory& mem);
    void drawActivity(Memory& mem);
    void drawCode(Registers& reg, Memory&mem);

    void clear(uint16_t colour);
    void px(int x, int y, uint16_t colour);
    void drawChar(int x, int y, char c, uint16_t colour);
    void drawText(int x, int y, const char* s, uint16_t colour);
    void drawHex(int x, int y, uint16_t v, uint16_t colour);
    static uint16_t rgb555(uint8_t r, uint8_t g, uint8_t b);
    static uint16_t lerp(uint16_t a, uint16_t b, uint8_t t);

    int scale_;
    SDL_Window* window_;
    SDL_Renderer* render_;
    SDL_Texture* texture_;
    uint16_t buf_[W * H];

    uint16_t prevGP_[GP_COUNT];
    uint8_t  flashGP_[GP_COUNT];
};

