#pragma once
#include <cstdint>
#include <fstream>
#include <vector>

#pragma pack(push,1)
struct TGAHeader {
    std::uint8_t  idlength{};   // 图像信息字段长度 
    std::uint8_t  colormaptype{};   // 颜色表类型
    std::uint8_t  datatypecode{};   // 图像类型码
    std::uint16_t colormaporigin{}; // 颜色表首地址
    std::uint16_t colormaplength{}; // 颜色表长度
    std::uint8_t  colormapdepth{};  // 颜色表项位数
    std::uint16_t x_origin{};   // 图像X坐标起始位置
    std::uint16_t y_origin{};   // 图像Y坐标起始位置
    std::uint16_t width{};  // 图像宽度
    std::uint16_t height{}; // 图像高度
    std::uint8_t  bitsperpixel{};   // 图像每像素存储占用位数
    std::uint8_t  imagedescriptor{};    // 图像描述字节
    // 图像信息字段 可变
    // 颜色表数据   可变
    // 图像数据     可变

};
#pragma pack(pop)

struct TGAColor {
    std::uint8_t bgra[4] = {0,0,0,0};
    std::uint8_t bytespp = {0};

    TGAColor() = default;
    TGAColor(const std::uint8_t R, const std::uint8_t G, const std::uint8_t B, const std::uint8_t A=255) : bgra{B,G,R,A}, bytespp(4) { }
    TGAColor(const std::uint8_t *p, const std::uint8_t bpp) : bytespp(bpp) {
        for (int i=bpp; i--; bgra[i] = p[i]);
    }
    std::uint8_t& operator[](const int i) { return bgra[i]; }
};

struct TGAImage {
    enum Format { GRAYSCALE=1, RGB=3, RGBA=4 };

    TGAImage() = default;
    TGAImage(const int w, const int h, const int bpp);
    bool  read_tga_file(const std::string filename);
    bool write_tga_file(const std::string filename, const bool vflip=true, const bool rle=true) const;
    void flip_horizontally();
    void flip_vertically();
    TGAColor get(const int x, const int y) const;
    void set(const int x, const int y, const TGAColor &c);
    int width()  const;
    int height() const;
private:
    bool   load_rle_data(std::ifstream &in);
    bool unload_rle_data(std::ofstream &out) const;

    int w   = 0;
    int h   = 0;
    int bpp = 0;
    std::vector<std::uint8_t> data = {};
};

