
#include "raylib.h"
#include <string.h>
#include <stdio.h>

#if defined(PLATFORM_WEB)
    #include <emscripten/emscripten.h>
#endif


Camera camera = { 0 };

int main() 
{
    // Initialization
    //--------------------------------------------------------------------------------------
    int map[6][6];
    memset(map, 0, sizeof(map));
    const int screenWidth = 1150;
    const int screenHeight = 675;
    float divider[8] = {2.2, 1.7, 1.4, 1.15, 1.0, 0.87};
    float pointerDivider[8] = {2.05, 1.62, 1.35, 1.11, 0.97, 0.845};
    int IsTurnToBlue = 0;
    int colTemp;
    int pointerThisCol;
    int i;
    int i2;
    int i3;
    int i4 = 0;
    int i5;
    Color colorCircle;
    int mode = 0;
    SetConfigFlags(FLAG_MSAA_4X_HINT);
    InitWindow(screenWidth, screenHeight, "raylib");
    camera.position = (Vector3){ 10.0f,  2.0f, 8.0f };
    camera.target = (Vector3){ 0.0f, 0.0f, 0.0f };
    camera.up = (Vector3){ 0.0f, 1.0f, 0.0f };
    camera.fovy = 60.0f;
    camera.projection = CAMERA_PERSPECTIVE;
    Texture2D PointerTextureMap = LoadTexture("textures/pointer.png");
     SetCameraMode(camera, CAMERA_FIRST_PERSON);

    //--------------------------------------------------------------------------------------

#if defined(PLATFORM_WEB)
    emscripten_set_main_loop(UpdateDrawFrame, 60, 1);
#else
    SetTargetFPS(60);               // Set our game to run at 60 frames-per-second
    //--------------------------------------------------------------------------------------
    ToggleFullscreen();
    i3 = 0;
    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        UpdateCamera(&camera);
        BeginDrawing();
        ClearBackground(RAYWHITE);
        for (i = 0; i < 6; i++){
            for (i2=0; i2< 6; i2++){
            switch(map[i][i2]){
            case 0:
                colorCircle = RAYWHITE;
                break;
            case 1:
                colorCircle = MAROON;
                break;
            case 2:
                colorCircle = BLUE;
                break;
            
            default:
                break;
            } 
            DrawCircleV((Vector2){(float)screenWidth/divider[i2], (float)screenHeight/divider[i] }, 40, colorCircle);
            }
        }
        if (IsKeyPressed(KEY_RIGHT)){
            i4++;
        }
        else if(IsKeyPressed(KEY_LEFT)){
            i4--;
        }
        if (i4 < 0){
            i4 = 5;
        }
        if (i4 > 5 ) {
                i4 = 0;
            }
        DrawTextureEx(PointerTextureMap, (Vector2){screenWidth/pointerDivider[i4], screenHeight/3.0}, 180.0,0.2, GRAY);
        /*if (IsKeyPressed())*/
        if (IsKeyDown(KEY_ENTER)){

            colTemp = i4;
            pointerThisCol = 0;
            for (i5 = 0; i5 < 5; i5++){
                printf("map[%i][%i] : %i\n",colTemp, i5, map[colTemp][i5]);
                if (map[colTemp][i5] != 0){
                    pointerThisCol = i5;
                    break;
                }
                
            }
            map[i5][colTemp] = 2; 
            i3++;
            if (i3 > 35){
                i3 = 1;
            }
        }
        DrawText("BLUE TURN", 20, 400, 10, BLACK);
        DrawFPS(10, 10);
        

        EndDrawing();

    }
#endif

    // De-Initialization
    //--------------------------------------------------------------------------------------
    CloseWindow();                  // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
