#pragma once
#include <fstream>
#include "framebuffer.h"

struct Bitmap{
    Framebuffer framebuffer = Framebuffer();
    const std::string filename = "out.bmp";
    std::vector<Vertex2> polygon1 = {Vertex2(165, 380), Vertex2(185, 360), Vertex2(180, 330), 
                                     Vertex2(207, 345), Vertex2(233, 330), Vertex2(230, 360),
                                     Vertex2(250, 380), Vertex2(220, 385), Vertex2(205, 410),
                                     Vertex2(193, 383)};

    std::vector<Vertex2> polygon2 = {Vertex2(321, 335), Vertex2(288, 286), Vertex2(339, 251), 
                                     Vertex2(374, 302)};
    
    std::vector<Vertex2> polygon3 = {Vertex2(377, 249), Vertex2(411, 197), Vertex2(436, 249)};

    std::vector<Vertex2> polygon4 = {Vertex2(413, 177), Vertex2(448, 159), Vertex2(502, 88), 
                                     Vertex2(553, 53), Vertex2(535, 36), Vertex2(676, 37), 
                                     Vertex2(660, 52), Vertex2(750, 145), Vertex2(761, 179), 
                                     Vertex2(672, 192), Vertex2(659, 214), Vertex2(615, 214), 
                                     Vertex2(632, 230), Vertex2(580, 230), Vertex2(597, 215), 
                                     Vertex2(552, 214), Vertex2(517, 144), Vertex2(466, 180)};
                                    
    std::vector<Vertex2> polygon5 = {Vertex2(682, 175), Vertex2(708, 120), Vertex2(735, 148),
                                     Vertex2(739, 170)};

    void render() {
        framebuffer.setClearColor(Color(0, 0, 0));
        framebuffer.clear();



        drawPolygon4();
        renderBuffer();
    }

    void renderBuffer() {
        const int width = framebuffer.framebufferWidth;
        const int height = framebuffer.framebufferHeight;

        constexpr int BMP_HEADER_SIZE = 14;
        constexpr int DIB_HEADER_SIZE = 40;
        const int paddingSize = (4 - (width * 3) % 4) % 4;
        const int fileSize = BMP_HEADER_SIZE + DIB_HEADER_SIZE + (3 * width + paddingSize) * height;

        char bmpHeader[BMP_HEADER_SIZE] = {
            'B', 'M',
            static_cast<char>(fileSize), static_cast<char>(fileSize >> 8), static_cast<char>(fileSize >> 16), static_cast<char>(fileSize >> 24),
            0, 0, 0, 0,
            static_cast<char>(BMP_HEADER_SIZE + DIB_HEADER_SIZE), static_cast<char>((BMP_HEADER_SIZE + DIB_HEADER_SIZE) >> 8), static_cast<char>((BMP_HEADER_SIZE + DIB_HEADER_SIZE) >> 16), static_cast<char>((BMP_HEADER_SIZE + DIB_HEADER_SIZE) >> 24)
        };

        char dibHeader[DIB_HEADER_SIZE] = {
            static_cast<char>(DIB_HEADER_SIZE), static_cast<char>(DIB_HEADER_SIZE >> 8), static_cast<char>(DIB_HEADER_SIZE >> 16), static_cast<char>(DIB_HEADER_SIZE >> 24),
            static_cast<char>(width), static_cast<char>(width >> 8), static_cast<char>(width >> 16), static_cast<char>(width >> 24),
            static_cast<char>(height), static_cast<char>(height >> 8), static_cast<char>(height >> 16), static_cast<char>(height >> 24),
            1, 0,
            24, 0,
            0, 0, 0, 0,
            static_cast<char>((3 * width + paddingSize) * height), static_cast<char>(((3 * width + paddingSize) * height) >> 8), static_cast<char>(((3 * width + paddingSize) * height) >> 16), static_cast<char>(((3 * width + paddingSize) * height) >> 24),
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0,
            0, 0, 0, 0
        };

        std::ofstream file(filename, std::ios::binary);
        if (!file) {
            std::cerr << "Error al abrir el archivo " << filename << std::endl;
            return;
        }

        file.write(bmpHeader, BMP_HEADER_SIZE);
        file.write(dibHeader, DIB_HEADER_SIZE);

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int index = y * width + x;
                Color color = framebuffer.framebuffer[index];
                file.write(reinterpret_cast<const char*>(&color.b), 1);
                file.write(reinterpret_cast<const char*>(&color.g), 1);
                file.write(reinterpret_cast<const char*>(&color.r), 1);
            }

            for (int i = 0; i < paddingSize; i++) {
                file.put(0);
            }
        }

        file.close();

        std::cout << "Archivo " << filename << " generado correctamente." << std::endl;
    }

    void drawPolygon1(){
        framebuffer.setCurrentColor(Color(255, 255, 255));
        framebuffer.drawPolygon(polygon1);
        framebuffer.setCurrentColor(Color(255, 255, 0));
        framebuffer.fillPolygon(polygon1);
    }

    void drawPolygon2(){
        framebuffer.setCurrentColor(Color(255, 255, 255));
        framebuffer.drawPolygon(polygon2);
        framebuffer.setCurrentColor(Color(0, 0, 255));
        framebuffer.fillPolygon(polygon2);
    }

    void drawPolygon3(){
        framebuffer.setCurrentColor(Color(255, 255, 255));
        framebuffer.drawPolygon(polygon3);
        framebuffer.setCurrentColor(Color(255, 0, 0));
        framebuffer.fillPolygon(polygon3);
    }

    void drawPolygon4(){
        framebuffer.setCurrentColor(Color(255, 255, 255));
        framebuffer.drawPolygon(polygon4);
        framebuffer.setCurrentColor(Color(0, 255, 0));
        framebuffer.fillPolygon(polygon4);
        framebuffer.setCurrentColor(Color(0, 0, 0));
        framebuffer.drawPolygon(polygon5);
        framebuffer.fillPolygon(polygon5);
    }

};