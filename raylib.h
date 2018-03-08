/* Fake raylib header file needed for raygui */
#ifndef RAYLIB_H
#define RAYLIB_H

#include "tigr.h"

#define KEY_RIGHT           262
#define KEY_LEFT            263
#define KEY_DOWN            264
#define KEY_UP              265
#define KEY_BACKSPACE_TEXT  259

#define MOUSE_LEFT_BUTTON   0

#define LIGHTGRAY           (Color){200, 200, 200, 255}
#define GRAY                (Color){130, 130, 130, 255}
#define WHITE               (Color){255, 255, 255, 255}
#define RAYWHITE            (Color){245, 245, 245, 255}
#define BLACK               (Color){0, 0, 0, 255}

typedef struct Color {
    unsigned char r;
    unsigned char g;
    unsigned char b;
    unsigned char a;
} Color;

typedef struct Rectangle {
    int x;
    int y;
    int width;
    int height;
} Rectangle;

typedef struct Texture2D {
    unsigned int id;
    int width;
    int height;
    int mipmaps;            // Mipmap levels, 1 by default
    int format;             // Data format (PixelFormat type)
} Texture2D;

typedef struct Vector2 {
    float x;
    float y;
} Vector2;

typedef struct Vector3 {
    float x;
    float y;
    float z;
} Vector3;

Color GetColor(int hexValue);
int ColorToInt(Color color);
Color Fade(Color color, float alpha);
bool CheckCollisionPointRec(Vector2 point, Rectangle rec);
const char *FormatText(const char *text, ...);

int MeasureText(const char *text, int fontSize);
void DrawText(const char *text, int posX, int posY, int fontSize, Color color);
void DrawRectangle(int x, int y, int width, int height, Color color);
void DrawRectangleRec(Rectangle rec, Color color);
Vector2 GetMousePosition(void);
bool IsMouseButtonDown(int button);
bool IsMouseButtonUp(int button);
bool IsMouseButtonReleased(int button);
int GetMouseWheelMove(void);
int GetKeyPressed(void);
bool IsKeyPressed(int key);
bool IsKeyDown(int key);
void DrawRectangleLines(int x, int y, int width, int height, Color color);
void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color);
void DrawRectangleGradientV(int posX, int posY, int width, int height, Color color1, Color color2);
void DrawRectangleGradientH(int posX, int posY, int width, int height, Color color1, Color color2);
void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, Color col4);
void DrawTexture(Texture2D texture, int posX, int posY, Color tint);
void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, Color tint);

#endif
