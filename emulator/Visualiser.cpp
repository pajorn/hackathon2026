#include "Visualiser.h"
#include "font8x8_basic.h"
#include <SDL.h>
#include <cstdio>
#include <cstring>

// layout
static const int REG_X = 8, REG_Y = 8;
static const int STK_X = 8, STK_Y = 200;
static const int ACT_X = 248, ACT_Y = 8;
static const int COD_X = 8, COD_Y = 310;
// colour
static const uint16_t C_BG    = 0x0000;
static const uint16_t C_TEXT  = 0x5AD6;
static const uint16_t C_DIM   = 0x2D6B;
static const uint16_t C_FLASH = 0x7FE0;   // yellow
static const uint16_t C_SP    = 0x03FF;   // cyan
static const uint16_t C_IP    = 0x7C00;   // red
static const uint16_t C_HOT   = 0x7FFF;   // white

Visualiser::Visualiser(int scale)
    : scale_(scale), window_(nullptr), render_(nullptr), texture_(nullptr), buf_{} {
        memset(prevGP_, 0, sizeof prevGP_);
        memset(flashGP_, 0, sizeof flashGP_);
}

Visualiser::~Visualiser() {
    if (texture_) SDL_DestroyTexture(texture_);
    if (render_) SDL_DestroyRenderer(render_);
    if (window_)   SDL_DestroyWindow(window_);
}

bool Visualiser::init() {
    window_ = SDL_CreateWindow("visualiser", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED,
            W * scale_, H * scale_, SDL_WINDOW_SHOWN);
    if (!window_) return false;
    render_ = SDL_CreateRenderer(window_, -1, SDL_RENDERER_ACCELERATED);
    if (!render_) return false;
    SDL_RenderSetLogicalSize(render_, W, H);
    texture_ = SDL_CreateTexture(render_, SDL_PIXELFORMAT_RGB555,
            SDL_TEXTUREACCESS_STREAMING, W, H);
    return texture_ != nullptr;
    // cba fucking shit
}

uint16_t Visualiser::rgb555(uint8_t r, uint8_t g, uint8_t b) {
    return (uint16_t)(((r >> 3) << 10) | ((g >> 3) << 5) | (b >> 3));
}

uint16_t Visualiser::lerp(uint16_t a, uint16_t b, uint8_t t) {
    int ar = (a >> 10) & 31, ag = (a >> 5) & 31, ab = a & 31;
    int br = (b >> 10) & 31, bg = (b >> 5) & 31, bb = b & 31;
    int r  = ar + ((br - ar) * t) / 255;
    int g  = ag + ((bg - ag) * t) / 255;
    int bl = ab + ((bb - ab) * t) / 255;
    return (uint16_t)((r << 10) | (g << 5) | bl);
}

void Visualiser::clear(uint16_t colour) {
    for (int i = 0; i < W * H; i++) buf_[i] = colour;
}

void Visualiser::px(int x, int y, uint16_t colour) {
    if (x < 0 || y < 0 || x >= W || y >= H) return;
    buf_[y * W + x] = colour;
}

void Visualiser::drawChar(int x, int y, char c, uint16_t colour) {
    const unsigned char* glyph = font8x8_basic[(int)c];
    for (int row = 0; row < 8; row++)
        for (int col =0; col < 8; col++)
            if (glyph[row] & (1 << col))
                px(x + col, y + row, colour);
}

void Visualiser::drawText(int x, int y, const char* s, uint16_t colour) {
    for (; *s; s++, x += 8) drawChar(x, y, *s, colour);
}

void Visualiser::drawHex(int x, int y, uint16_t v, uint16_t colour) {
    char s[8];
    snprintf(s, sizeof s, "%04X", v);
    drawText(x, y, s, colour);
}

// windows
void Visualiser::drawRegisters(Registers& reg) {
    char label[8];
    for (int i = 0; i < GP_COUNT; i++) {
        uint16_t v = reg.getGP((uint8_t)i);
        if (v != prevGP_[i]) flashGP_[i] = 255;
        uint16_t c = lerp(C_TEXT, C_FLASH, flashGP_[i]);
        int y = REG_Y + i * 10;
        snprintf(label, sizeof label, "r%d", i);
        drawText(REG_X, y, label, C_DIM);
        drawHex(REG_X + 32, y, v, c);
        flashGP_[i] -= flashGP_[i] >> 2;
        prevGP_[i] = v;
    }
    int y = REG_Y + GP_COUNT * 10 + 4;
    drawText(REG_X, y,      "ip", C_DIM); drawHex(REG_X + 32, y, reg.getIP(), C_IP);
    drawText(REG_X, y + 10, "sp", C_DIM); drawHex(REG_X + 32, y + 10, reg.getSP(), C_SP);
    drawText(REG_X, y + 20, "N", reg.getNegative() ? C_FLASH : C_DIM);
    drawText(REG_X + 16, y + 20, "E", reg.getEqual() ? C_FLASH : C_DIM);
}

void Visualiser::drawStack(Registers& reg, Memory& mem) {
    const uint16_t TOP = 0xC000;
    const int MAX_ROWS = 9;
    uint16_t sp = reg.getSP();
    int depth = TOP - sp;
    if (depth > MAX_ROWS) depth = MAX_ROWS;

    drawText(STK_X, STK_Y, "stack", C_DIM);
    for (int i = 0; i < depth; i ++) {
        uint16_t addr = (uint16_t)(TOP - 1 - i);
        int y = STK_Y + 12 + i * 10;
        bool top = (addr == sp);
        drawText(STK_X, y, top ? ">" : " ", C_SP);
        drawHex(STK_X + 12, y, addr, C_DIM);
        drawHex(STK_X + 56, y, mem.read(addr), top ? C_SP : C_TEXT);
    }
}

void Visualiser::drawActivity(Memory& mem) {
    const uint8_t* act = mem.activity();
    for (int a = 0; a < Memory::SIZE; a++) {
        int x = ACT_X + (a & 0xFF);
        int y = ACT_Y + (a >> 8);
        uint16_t base;
        if (a >= 0xC000) base = rgb555(0, 0, 32); // pixel
        else if (a >= 0x8000) base = rgb555(0, 24, 24); // stack
        else base = rgb555(10, 10, 10);
        px(x, y, lerp(base, C_HOT, act[a]));
    }
}

void Visualiser::drawCode(Registers& reg, Memory& mem) {
    uint16_t ip = reg.getIP();
    for (int i = -1; i <= 2; i++) {
        uint16_t a = (uint16_t)(ip + i);
        int y = COD_Y + (i + 1) * 10;
        bool cur = (i == 0);
        drawText(COD_X, y, cur ? ">" : " ", C_IP);
        drawHex(COD_X + 12, y, a, C_DIM);
        drawHex(COD_X + 56, y, mem.read(a), cur ? C_IP : C_TEXT);
    }
}

void Visualiser::draw(Registers& reg, Memory& mem, bool paused) {
    clear(C_BG);
    drawActivity(mem);
    drawRegisters(reg);
    drawStack(reg, mem);
    drawCode(reg, mem);
    if (paused) drawText(W - 8 * 7, H - 12, "pause", C_FLASH);
    SDL_UpdateTexture(texture_, nullptr, buf_, W * sizeof(uint16_t));
    SDL_RenderClear(render_);
    SDL_RenderCopy(render_, texture_, nullptr, nullptr);
    SDL_RenderPresent(render_);
}







