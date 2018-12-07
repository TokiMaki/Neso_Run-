#include "stdafx.h"
#include "Run_time_Framework.h"

CRun_time_Framework fx;

void main(int argc, char *argv[]) {
	glutInit(&argc, argv);
	fx.Registeridle([]() {fx.Update(); });
	fx.RegisterRender([]() {fx.draw(); });
	fx.RegisterKeyboardDown([](unsigned char key, int x, int y) {fx.KeyboardDown(key, x, y); });
	fx.RegisterSpecialKeyboardDown([](int key, int x, int y) {fx.SpecialKeyboardDown(key, x, y); });
	fx.RegisterKeyboardUp([](unsigned char key, int x, int y) {fx.KeyboardUp(key, x, y); });
	fx.RegisterMouse([](int state, int button, int x, int y) {fx.Mouse(state, button, x, y); });
	fx.RegisterMouseMove([](int x, int y) {fx.PassiveMotion(x, y); });
	fx.RegisterResize([](int w, int h) {fx.Reshape(w, h); });
	fx.Init();
	glutMainLoop();
}