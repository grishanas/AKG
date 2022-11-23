#ifndef __MAIN_H__
#define __MAIN_H__

constexpr int width = 800;
constexpr int height = 800;
constexpr int depth = 255;


struct pix {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char t;
};

struct pix_32 {
    uint32_t rgbt;
};

#endif //__MAIN_H__ 
