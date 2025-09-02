//============================================================================
// Name        : raylib-old-school-plasma-effect.cpp
// Author      : 
// Version     :
// Copyright   : Your copyright notice
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>

#define PLATFORM_DESKTOP_SDL
#define RLGL_IMPLEMENTATION
#define RLGL_SHOW_GL_DETAILS_INFO
#define RLGL_ENABLE_OPENGL_DEBUG_CONTEXT
#define GRAPHICS_API_OPENGL_43
#define SUPPORT_TRACELOG

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

#define flip_y(h,y) (h-y)

#include "raylib.h"

#include "rlgl.h"

using namespace std;

int main() {

	InitWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "OlD-ScHoOl PlAsMa eFfEcT");

	//Image image = LoadImage("../crysis-2.jpg");

	Image image = LoadImage("../one-screen-3-vanity.png");

	ImageFormat(&image,PIXELFORMAT_UNCOMPRESSED_R8G8B8A8);
	ImageResize(&image,WINDOW_WIDTH,WINDOW_HEIGHT);
	Texture image_texture = LoadTextureFromImage(image);
	int screenWidth = image_texture.width;
	int screenHeight = image_texture.height;

	Camera2D camera = {0};
	camera.zoom = 1.0f;

	camera.offset = (Vector2){ screenWidth/2.0f, screenHeight/2.0f };

	RenderTexture2D final_target = LoadRenderTexture(screenWidth, screenHeight);
	BeginTextureMode(final_target);
	ClearBackground(BLANK);
	EndTextureMode();

	// get compute shader code and compile

	char *compute_shader_raycast2d_code = LoadFileText("cs_plasma_effect.comp");
	unsigned int compiled_plasma_effect_compute_shader = rlCompileShader(compute_shader_raycast2d_code, RL_COMPUTE_SHADER);
	if (compiled_plasma_effect_compute_shader == 0 ){
		printf("error occurred during compute shader compilation. \n");
	}
	unsigned int compute_shader_program = rlLoadComputeShaderProgram(compiled_plasma_effect_compute_shader);
	//int u_image_location = rlGetLocationUniform(compute_shader_program,"u_image");
	int output_image_location= rlGetLocationUniform(compute_shader_program,"u_output_image");
	int input_image_location= rlGetLocationUniform(compute_shader_program,"u_input_image");

	float current_time = 0;
	float frequency[2] = {1,24};
	SetTargetFPS(120);
	// Main game loop
	    while (!WindowShouldClose())        // Detect window close button or ESC key
	    {


	        // we use compute shader to render to this texture

	        rlEnableShader(compute_shader_program);

	            rlSetUniform(3,(void *)(&current_time),RL_SHADER_UNIFORM_FLOAT,1);
	            rlSetUniform(4,(void *)frequency,RL_SHADER_UNIFORM_VEC2,1);

	            rlActiveTextureSlot(input_image_location);
	            rlEnableTexture(input_image_location);
				rlBindImageTexture(image_texture.id,0,image_texture.format,false);

	            rlActiveTextureSlot(output_image_location);
	            rlEnableTexture(output_image_location);
	            rlBindImageTexture(final_target.texture.id,1,final_target.texture.format,false);

	            rlComputeShaderDispatch(screenWidth/8, screenHeight/8, 1); // Each GPU unit will process a command!
	        rlDisableShader();

	        // we draw the final image
	        BeginDrawing();

	            ClearBackground(BLANK);
	            DrawTexture(final_target.texture, 0, 0, WHITE);
	            DrawFPS(GetScreenWidth() - 100, 10);

	        EndDrawing();

	        //std::this_thread::sleep_for(std::chrono::milliseconds(10));
	        current_time += 0.001;
	        //----------------------------------------------------------------------------------
	    }



	    // De-Initialization
	    //--------------------------------------------------------------------------------------
	    CloseWindow();        // Close window and OpenGL context
	    //--------------------------------------------------------------------------------------
	    return 0;

}
