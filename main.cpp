#include <raylib.h>


int main(){
	InitWindow(800,600,"GrabFightEvacuate");
	
	InitAudioDevice();
	
	SetTargetFPS(120);
	SetTraceLogLevel(LOG_ALL);
	
	bool isFull=false;
	Vector2 orgposxy;
	int orgwx=0,orgwy=0;
	while(!WindowShouldClose()){
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
		
		BeginDrawing();
		
		ClearBackground(RAYWHITE);
		
		EndDrawing();
		
	}
	
	CloseAudioDevice();
	
	CloseWindow(); 
	
	return 0;
}
