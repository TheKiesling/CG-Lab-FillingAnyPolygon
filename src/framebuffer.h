#pragma once
#include <vector>
#include "color.h"
#include "vertex2.h"
#include <algorithm>

struct Framebuffer {
    const int framebufferWidth = 800;
    const int framebufferHeight = 600;
    Color clearColor;
    Color currentColor;
    std::vector<Color> framebuffer;

    Framebuffer(Color clearColor = Color(0, 0, 0))
        : clearColor(clearColor),
          currentColor(Color(255, 255, 255)), 
          framebuffer(framebufferWidth * framebufferHeight, clearColor) {}

    void setClearColor(Color color) {
        clearColor = color;
    }

    void setCurrentColor(Color color) {
        currentColor = color;
    }

    void clear() {
        std::fill(framebuffer.begin(), framebuffer.end(), clearColor);
    }

    void point(Vertex2 vertex) {
        int x = static_cast<int>(vertex.x);
        int y = static_cast<int>(vertex.y);

        if (x >= 0 && x < framebufferWidth && y >= 0 && y < framebufferHeight) {
            int index = y * framebufferWidth + x;
            framebuffer[index] = currentColor;
        }
    }

    void drawLine(float x1, float y1, float x2, float y2) {
        int x1_int = static_cast<int>(x1);
        int y1_int = static_cast<int>(y1);
        int x2_int = static_cast<int>(x2);
        int y2_int = static_cast<int>(y2);

        int dx = abs(x2_int - x1_int);
        int dy = abs(y2_int - y1_int);
        int sx = x1_int < x2_int ? 1 : -1;
        int sy = y1_int < y2_int ? 1 : -1;
        int err = dx - dy;

        while (true) {
            point(Vertex2(x1_int, y1_int));

            if (x1_int == x2_int && y1_int == y2_int) {
                break;
            }

            int e2 = 2 * err;
            if (e2 > -dy) {
                err -= dy;
                x1_int += sx;
            }
            if (e2 < dx) {
                err += dx;
                y1_int += sy;
            }
        }
    }

    void drawPolygon(const std::vector<Vertex2>& points) {
        if (points.size() < 2) {
            return; 
        }

        for (size_t i = 0; i < points.size() - 1; ++i) {
            drawLine(points[i].x, points[i].y, points[i + 1].x, points[i + 1].y);
        }

        drawLine(points.back().x, points.back().y, points[0].x, points[0].y);
    }

    void fillPolygon(const std::vector<Vertex2>& vertices) {
        int minY = framebufferHeight - 1;
        int maxY = 0;
        for (const auto& vertex : vertices) {
            int y = static_cast<int>(vertex.y);
            minY = std::min(minY, y);
            maxY = std::max(maxY, y);
        }

        for (int y = minY; y <= maxY; y++) {
            std::vector<float> intersections;
            for (size_t i = 0; i < vertices.size(); i++) {
                size_t nextIdx = (i + 1) % vertices.size();
                int y0 = static_cast<int>(vertices[i].y);
                int y1 = static_cast<int>(vertices[nextIdx].y);
                if ((y0 <= y && y1 > y) || (y1 <= y && y0 > y)) {
                    float x = vertices[i].x + (static_cast<float>(y - y0) / (y1 - y0)) * (vertices[nextIdx].x - vertices[i].x);
                    intersections.push_back(x);
                }
            }

            std::sort(intersections.begin(), intersections.end());

            for (size_t i = 0; i + 1 < intersections.size(); i += 2) {
                int x0 = static_cast<int>(intersections[i]);
                int x1 = static_cast<int>(intersections[i + 1]);
                for (int x = x0; x <= x1; x++) {
                    point(Vertex2(static_cast<float>(x), static_cast<float>(y)));
                }
            }
        }
    }
};
