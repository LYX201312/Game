#include <raylib.h>

#include <math.h>
#include <raymath.h>

#include <iostream>

const float Sensitivity=0.25f; //灵敏度
const int WndInitWidth=800; //初始宽
const int WndInitHeight=600; //初始高
float defWalkingSpeed=0.08f;

using namespace std;

int main(){
	SetConfigFlags(FLAG_MSAA_4X_HINT);
	SetConfigFlags(FLAG_WINDOW_RESIZABLE);
	
	InitWindow(WndInitWidth,WndInitHeight,"GrabFightEvacuate");
	InitAudioDevice();
	
	SetTargetFPS(120);
	SetTraceLogLevel(LOG_WARNING);
	SetExitKey(KEY_NULL);
	
	DisableCursor();
	
	bool isFull=false;
	Vector2 orgposxy;
	int orgwx=0,orgwy=0;
	
	Camera3D cam={0};
	cam.position=(Vector3){2.0f,1.0f,0.0f};
	cam.target=(Vector3){0.0f,0.0f,0.0f};
	cam.up=(Vector3){0.0f,1.0f,0.0f};
	cam.fovy=80.0f;
	cam.projection=CAMERA_PERSPECTIVE;
	
	Mesh mesh=GenMeshCube(1,1,1);
	
	int clrHue=0;
	bool isBH=true;
	bool isDbg=false;
	
	Vector2 mousedelta={0};
	
	while(!WindowShouldClose()){	
		mousedelta={0};
		
		//全屏逻辑
		if(IsKeyPressed(KEY_F11)){
			if(isFull){
				ToggleBorderlessWindowed();
				
				SetWindowPosition(orgposxy.x,orgposxy.y);
				SetWindowSize(orgwx,orgwy);
			}else{
				orgposxy=GetWindowPosition();
				orgwx=GetRenderWidth();
				orgwy=GetRenderHeight();
				
				ToggleBorderlessWindowed();
				
				SetWindowPosition(0,0);
				SetWindowSize(GetScreenWidth(),GetScreenHeight());
			}
			isFull=!isFull;
		}
		
		//是否显示Debug界面
		if(IsKeyPressed(KEY_F3)){
			isDbg=!isDbg;
		}
		
		//是否捕获鼠标
		if(IsKeyDown(KEY_ESCAPE)){
			EnableCursor();
			isBH=false;
		}else if(IsMouseButtonDown(MOUSE_BUTTON_LEFT)){
			DisableCursor();
			isBH=true;
		}
		if(isBH){
			mousedelta=GetMouseDelta();
			SetMousePosition(GetScreenWidth()/2,GetScreenHeight()/2);
		}
		//更新相机位置
		UpdateCameraPro(&cam,
			(Vector3){
				IsKeyDown(KEY_W)*defWalkingSpeed-IsKeyDown(KEY_S)*defWalkingSpeed,
				IsKeyDown(KEY_D)*defWalkingSpeed-IsKeyDown(KEY_A)*defWalkingSpeed,
				IsKeyDown(KEY_SPACE)*defWalkingSpeed/2-IsKeyDown(KEY_LEFT_SHIFT)*defWalkingSpeed/2
			},
			(Vector3){mousedelta.x*Sensitivity,mousedelta.y*Sensitivity,0},
			0.0f
			);
		
		//更新帧
		double time=GetTime();
		clrHue++;
		clrHue%=360;
		
		//创建贴图
		Image img=GenImageChecked(2,2,1,1,ColorFromHSV(clrHue,1,1),LIGHTGRAY);
		Texture2D texture=LoadTextureFromImage(img);
		UnloadImage(img);
		
		//创建材质
		Material material=LoadMaterialDefault();
		material.maps[MATERIAL_MAP_DIFFUSE].texture=texture;
		
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		
		BeginMode3D(cam);
		
		DrawMesh(mesh,material,MatrixIdentity());
		
		EndMode3D();
		
		//画调试屏幕
		if(isDbg){
			string F3=(string)"FPS:"+to_string(GetFPS())+"\n"+"X:"+to_string(cam.position.x)+" Y:"+to_string(cam.position.y)+" Z:"+to_string(cam.position.z);
			DrawText(F3.c_str(),0,0,30,BLACK);
		}
		
		EndDrawing();
		
		UnloadMaterial(material);
		UnloadTexture(texture);
		
		WaitTime(0.001);
		
	}
	
	EnableCursor();
	
	UnloadMesh(mesh);
	
	CloseAudioDevice();
	CloseWindow(); 
	
	return 0;
}
