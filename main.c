#include <stdbool.h>
#include <stdarg.h>

#include "tigr.h"

/* Raygui are not working as standalone version without raylib. We need fake 
 * raylib.h */
#include "raylib.h"
#define RAYGUI_IMPLEMENTATION
// #define RAYGUI_STANDALONE
#include "raygui.h"

Tigr   *screen;
bool    quit;
Vector2 mouseCoords;
int     mouseX;
int     mouseY;
int     mouseButtonsMask;
int     mouseButtons[3];
int     previousMouseButtons[3];
bool    checkboxChecked;

int KeyTigrToRaylib(int key)
{
    if ((key >= 32) && (key <= 125))
        return key;
    else
        switch (key) {
            case TK_PAD0:
            case TK_PAD1:
            case TK_PAD2:
            case TK_PAD3:
            case TK_PAD4:
            case TK_PAD5:
            case TK_PAD6:
            case TK_PAD7:
            case TK_PAD8:
            case TK_PAD9:
                return key - 80;
            case TK_LEFT:
                return KEY_LEFT;
            case TK_RIGHT:
                return KEY_RIGHT;
            case TK_UP:
                return KEY_UP;
            case TK_DOWN:
                return KEY_DOWN;
            case TK_BACKSPACE:
                return KEY_BACKSPACE_TEXT;
            case TK_PADMUL:
                return '*';
            case TK_PADADD:
                return '+';
            case TK_MINUS:
            case TK_PADSUB:
                return '-';
            case TK_DOT:
            case TK_PADDOT:
                return '.';
            case TK_SLASH:
            case TK_PADDIV:
                return '/';
            case TK_SEMICOLON:
                return ';';
            case TK_EQUALS:
                return '=';
            case TK_COMMA:
                return ',';
            case TK_TICK:
            case TK_BACKTICK:
                return '\'';
            case TK_LSQUARE:
                return '[';
            case TK_RSQUARE:
                return ']';
            case TK_BACKSLASH:
                return '\\';
            default:
                return 0;
        }
}

int KeyRaylibToTigr(int key)
{
    if ((key >= 32) && (key <= 125))
        return key;
    else
        switch (key) {
            case KEY_LEFT:
                return TK_LEFT;
            case KEY_RIGHT:
                return TK_RIGHT;
            case KEY_UP:
                return TK_UP;
            case KEY_DOWN:
                return TK_DOWN;
            case KEY_BACKSPACE_TEXT:
                return TK_BACKSPACE;
            default:
                return 0;
        }
}

static inline TPixel ColorRaylibToTigr(Color color)
{
    TPixel resultColor;
    resultColor.r = color.r;
    resultColor.g = color.g;
    resultColor.b = color.b;
    resultColor.a = color.a;
    
    return resultColor;
}

int MeasureText(const char *text, int fontSize)
{ 
    return tigrTextWidth(tfont, text);
}

void DrawText(const char *text, int posX, int posY, int fontSize, Color color) 
{ 
    tigrPrint(screen, tfont, posX, posY, ColorRaylibToTigr(color), "%s", text);
}

void DrawRectangle(int x, int y, int width, int height, Color color) 
{ 
    tigrFill(screen, x, y, width, height, ColorRaylibToTigr(color));
}

void DrawRectangleRec(Rectangle rec, Color color) 
{ 
    DrawRectangle(rec.x, rec.y, rec.width, rec.height, color); 
}

Vector2 GetMousePosition(void) 
{ 
    return mouseCoords; 
}

bool IsMouseButtonDown(int button)
{
    return mouseButtons[button];
}

bool IsMouseButtonUp(int button)
{
    return !mouseButtons[button];
}

bool IsMouseButtonReleased(int button)
{
    return ((mouseButtons[button] == false) && 
     (previousMouseButtons[button] == true));
}

int GetMouseWheelMove(void)
{
    /* Not provided by tigr */
    return 0;
}

int GetKeyPressed(void)
{
    return KeyTigrToRaylib(tigrReadChar(screen));
}

bool IsKeyPressed(int key)
{
    return tigrKeyDown(screen, KeyRaylibToTigr(key));
}

bool IsKeyDown(int key)
{
    return tigrKeyHeld(screen, KeyRaylibToTigr(key));
}

void DrawRectangleLines(int x, int y, int width, int height, Color color) 
{ 
    tigrRect(screen, x, y, width, height, ColorRaylibToTigr(color));
}

void DrawRectangleLinesEx(Rectangle rec, int lineThick, Color color)
{
    tigrRect(screen, rec.x, rec.y, rec.width, rec.height, 
     ColorRaylibToTigr(color));
}

void DrawRectangleGradientV(int posX, int posY, int width, int height, 
 Color color1, Color color2)
{
    /* TODO */
}

void DrawRectangleGradientH(int posX, int posY, int width, int height, 
 Color color1, Color color2)
{
    /* TODO */
}

void DrawRectangleGradientEx(Rectangle rec, Color col1, Color col2, Color col3, 
 Color col4)
{
    /* TODO */
}

void DrawTexture(Texture2D texture, int posX, int posY, Color tint)
{
    /* TODO */
}

void DrawTextureRec(Texture2D texture, Rectangle sourceRec, Vector2 position, 
 Color tint)
{
    /* TODO */
}

// Returns a Color struct from hexadecimal value
Color GetColor(int hexValue)
{
    Color color;

    color.r = (unsigned char)(hexValue >> 24) & 0xFF;
    color.g = (unsigned char)(hexValue >> 16) & 0xFF;
    color.b = (unsigned char)(hexValue >> 8) & 0xFF;
    color.a = (unsigned char)hexValue & 0xFF;

    return color;
}

// Returns hexadecimal value for a Color
int ColorToInt(Color color)
{
    return (((int)color.r << 24) | ((int)color.g << 16) | ((int)color.b << 8) | 
     (int)color.a);
}

// Check if point is inside rectangle
bool CheckCollisionPointRec(Vector2 point, Rectangle rec)
{
    if ((point.x >= rec.x) && (point.x <= (rec.x + rec.width)) && 
     (point.y >= rec.y) && (point.y <= (rec.y + rec.height))) 
        return true;

    return false;
}

// Color fade-in or fade-out, alpha goes from 0.0f to 1.0f
Color Fade(Color color, float alpha)
{
    if (alpha < 0.0f) alpha = 0.0f;
    else if (alpha > 1.0f) alpha = 1.0f;

    return (Color){color.r, color.g, color.b, (unsigned char)(255.0f * alpha)};
}

// Formatting of text with variables to 'embed'
const char *FormatText(const char *text, ...)
{
    #define MAX_FORMATTEXT_LENGTH   64

    static char buffer[MAX_FORMATTEXT_LENGTH];

    va_list args;
    va_start(args, text);
    vsprintf(buffer, text, args);
    va_end(args);

    return buffer;
}

void MouseUpdate(void)
{
    int i;
    memcpy(previousMouseButtons, mouseButtons, sizeof(int) * 3U);
    tigrMouse(screen, &mouseX, &mouseY, &mouseButtonsMask);
    for (i = 0; i < 3; i++)
        mouseButtons[i] = ((mouseButtonsMask & (1 << i)) == (1 << i));
    mouseCoords.x = mouseX;
    mouseCoords.y = mouseY;
}

int main(int argc, char **argv)
{
    checkboxChecked = false;
    
    quit = false;
    
    screen = tigrWindow(640, 480, "Raygui Helloworld", TIGR_FIXED);
    
    GuiEnable();
    
    while (!quit) {
        MouseUpdate();
        
        if (tigrClosed(screen)) {
            quit = true;
        }
        
        /* Render */
        tigrClear(screen, tigrRGB(0x00, 0x00, 0x00));
        
        GuiLabel((Rectangle){32, 32, 64, 64}, "Hello");
        
        checkboxChecked = GuiCheckBox((Rectangle){32, 64, 16, 16}, 
         checkboxChecked);
         
        /* Your other widgets here */
        
        tigrUpdate(screen);
    }
    
    GuiDisable();
    
    tigrFree(screen);
    
    return 0;
}
