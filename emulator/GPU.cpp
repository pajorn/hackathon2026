#include "GPU.h"
#include <SDL.h>
#include <cstdio>
#include <cstring>

GPU::GPU(int scale) : scale_(scale), sdlReady_(false), quit_(false), window_(nullptr), renderer_(nullptr), texture_(nullptr), buffer_{} {
}

GPU::~GPU() {
    if (texture_) SDL_DestroyTexture(texture_);
    if (renderer_) SDL_DestroyRenderer(renderer_);
    if (window_) SDL_DestroyWindow(window_);
    if (sdlReady_) SDL_Quit();
}

bool GPU::init() {
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL_Init failure: %s\n", SDL_GetError());
        return false;
    }
    sdlReady_ = true;
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "0");

    window_ = SDL_CreateWindow("emulator", 100, 200, WIDTH * scale_, HEIGHT * scale_, SDL_WINDOW_SHOWN);
    if (!window_) {
        fprintf(stderr, "SDL_CreateWindow failure: %s\n", SDL_GetError());
        return false;
    }

    renderer_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer_) {
        fprintf(stderr, "SDL_Renderer failure: %s\n", SDL_GetError());
        return false;
    }
    SDL_RenderSetLogicalSize(renderer_, WIDTH, HEIGHT);

    texture_ = SDL_CreateTexture(renderer_, SDL_PIXELFORMAT_RGB555, SDL_TEXTUREACCESS_STREAMING, WIDTH, HEIGHT);
    if (!texture_) {
        fprintf(stderr, "SDL_Texture failure: %s\n", SDL_GetError());
        return false;
    }
    return true;
}

void GPU::pollEvents() {
    SDL_Event e;
    while (SDL_PollEvent(&e)) {
        switch (e.type) {
            case SDL_QUIT:
                quit_ = true;
                break;
            case SDL_KEYDOWN:
                switch (e.key.keysym.sym) {
                    case SDLK_ESCAPE: quit_ = true; break;
                    case SDLK_SPACE: if (!e.key.repeat) pause = true; ; break;
                    case SDLK_PERIOD: step = true; break;
                    case SDLK_r: if (!e.key.repeat) restart = true; break;
                    default:break;
                }
            default:
                break;
        }
    }
}

bool GPU::shouldQuit() {
    return quit_;
}

void GPU::drawFrame(Memory* memory) {
    memory->exportPixelBuffer(buffer_);
    present(buffer_);
}

void GPU::present(uint16_t* pixels) {
    if (!renderer_ || !texture_)    
        return;
    SDL_UpdateTexture(texture_, nullptr, pixels, WIDTH * sizeof(uint16_t));
    SDL_RenderClear(renderer_);
    SDL_RenderCopy(renderer_, texture_, nullptr, nullptr);
    SDL_RenderPresent(renderer_);
}

uint16_t GPU::rgb555(uint8_t r, uint8_t g, uint8_t b) {
    return (uint16_t)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3));
}

void GPU::test(uint16_t* out) {
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
        bool border = (x == 0 || y == 0 || x == WIDTH-1 || y == HEIGHT -1);
        out[y * WIDTH + x] = border
            ? rgb555(255, 255, 255)
            : rgb555((uint8_t)(x*2), (uint8_t)(y*2), 0x40);
        }
    }
}












