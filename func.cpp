#include "stdafx.h"
#include "Run_time_Framework.h"
#include "GamePlayScene.h"

#define pi 3.141592

GLvoid CRun_time_Framework::Key_Update() {

	if (dir & DIR_X) {		// ��Ʈ ������ &�� �� �ϳ�!
		glPushMatrix();
		{
			glRotatef(0.5f * (current_time - Prevtime), 1.f, 0.f, 0.f);		// ������ ����� �����ӿ� ���� �ӵ��� ����������
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR_Y) {
		glPushMatrix();
		{
			glRotatef(0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR_Z) {
		glPushMatrix();
		{
			glRotatef(0.5f * (current_time - Prevtime), 0.f, 0.f, 1.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}
	if (dir & DIR__X) {
		glPushMatrix();
		{
			glRotatef(-0.5f * (current_time - Prevtime), 1.f, 0.f, 0.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR__Y) {
		glPushMatrix();
		{
			glRotatef(-0.5f * (current_time - Prevtime), 0.f, 1.f, 0.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & DIR__Z) {
		glPushMatrix();
		{
			glRotatef(-0.5f * (current_time - Prevtime), 0.f, 0.f, 1.f);
			glMultMatrixf(identity);
			glGetFloatv(GL_MODELVIEW_MATRIX, identity);
		}
		glPopMatrix();
	}

	if (dir & Camera_ZOOM) {
		camera_zoom += 5;
	}

	if (dir & Camera__ZOOM) {
		camera_zoom -= 5;
	}

	if (camera_view & Camera_X) {
		camera_x += 5;
	}
	if (camera_view & Camera__X) {
		camera_x -= 5;
	}

	if (camera_view & Camera_Y) {
		camera_y += 5;
	}

	if (camera_view & Camera__Y) {
		camera_y -= 5;
	}

	if (camera_view & Camera_Z) {
		camera_z += 5;
	}

	if (camera_view & Camera__Z) {
		camera_z -= 5;
	}

	if (camera_move & Cameramv_X) {
		camera.x += 5;
	}
	if (camera_move & Cameramv__X) {
		camera.x -= 5;
	}
	if (camera_move & Cameramv_Y) {
		camera.y += 5;
	}
	if (camera_move & Cameramv__Y) {
		camera.y -= 5;
	}

}

GLvoid CRun_time_Framework::background(float r, float g, float b) {
	glClearColor(r, g, b, 1.0f); // �������� 'blue' �� ����
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // ������ ������ ��ü�� ĥ�ϱ�
}

GLvoid CGamePlayScene::vari_init() {

	memset(identity, 0, sizeof(identity));
	identity[0] = identity[5] = identity[10] = identity[15] = 1;		// ��� �ʱ�ȭ

	main_road = NULL;

	player.dir = 0;
	Create_Road();
}

GLvoid CGamePlayScene::shape_draw() {

	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	/*
	if (mod == 0) {
		gluLookAt(camera.x, camera.y, camera_zoom, 0, 0, -100, sin(camera_z / 180 * pi), cos(camera_z / 180 * pi), 0.0);
		glMultMatrixf(identity);
	}
	*/
	gluLookAt(player.x + sin(pi / 180 * (player.camera_rotate)) * 20, 20, player.z + cos(pi / 180 * (player.camera_rotate)) * 20, player.x, player.y + 20, player.z, 0, 1, 0);


	glPushMatrix();
	glColor3f(1, 0, 0);
	Draw_Ball();
	glPopMatrix();

	glPushMatrix();

	glColor3f(0.5, 0.5, 0.5);
	Draw_Road();
	glPopMatrix();


	glPopMatrix();

}

bool CGamePlayScene::Isin_Rect(int x1, int y1, int x2, int y2, int w1, int h1, int w2, int h2)
{
	if (x1 < w2 && y1 < h2 && x2 > w1 && y2 > h1)
	{
		return true;
	}

	return false;
}

GLubyte * CRun_time_Framework::LoadDIBitmap(const char *filename, BITMAPINFO ** info)
{
	FILE *fp;
	GLubyte *bits;
	int bitsize, infosize;
	BITMAPFILEHEADER header;

	// ���̳ʸ� �б� ���� ������ ���� 
	if ((fp = fopen(filename, "rb")) == NULL)
		return NULL;

	// ��Ʈ�� ���� ����� �д´�. 
	if (fread(&header, sizeof(BITMAPFILEHEADER), 1, fp) < 1) {
		fclose(fp);
		return NULL;
	}

	// ������ BMP �������� Ȯ���Ѵ�. 
	if (header.bfType != 'MB') {
		fclose(fp);
		return NULL;
	}

	// BITMAPINFOHEADER ��ġ�� ����. 
	infosize = header.bfOffBits - sizeof(BITMAPFILEHEADER);

	// ��Ʈ�� �̹��� �����͸� ���� �޸� �Ҵ��� �Ѵ�. 
	if ((*info = (BITMAPINFO *)malloc(infosize)) == NULL) {
		fclose(fp);
		exit(0);
		return NULL;
	}

	// ��Ʈ�� ���� ����� �д´�. 
	if (fread(*info, 1, infosize, fp) < (unsigned int)infosize) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// ��Ʈ���� ũ�� ���� 
	if ((bitsize = (*info)->bmiHeader.biSizeImage) == 0)
		bitsize = ((*info)->bmiHeader.biWidth*(*info)->bmiHeader.biBitCount + 7) / 8.0 *  abs((*info)->bmiHeader.biHeight);

	// ��Ʈ���� ũ�⸸ŭ �޸𸮸� �Ҵ��Ѵ�. 
	if ((bits = (unsigned char *)malloc(bitsize)) == NULL) {
		free(*info);
		fclose(fp);
		return NULL;
	}

	// ��Ʈ�� �����͸� bit(GLubyte Ÿ��)�� �����Ѵ�. 
	if (fread(bits, 1, bitsize, fp) < (unsigned int)bitsize) {
		free(*info);
		free(bits);
		fclose(fp);
		return NULL;
	}
	fclose(fp);
	return bits;
}

GLvoid CRun_time_Framework::set_texture()
{
	// n���� �̹��� �ؽ�ó ������ �Ѵ�.
	glGenTextures(5, titleTex);

	//�ؽ�ó�� ��ü�� �����Ѵ�. --- (1) 
	glBindTexture(GL_TEXTURE_2D, titleTex[0]);

	//�̹��� �ε��� �Ѵ�. --- (2) 
	pBytes = LoadDIBitmap("texture/ui/logo.bmp", &info);

	//�ؽ�ó ���� ���Ǹ� �Ѵ�. --- (3) 
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);

	//�ؽ�ó �Ķ���� ���� --- (4) 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

	// �ؽ�ó ��� ���� 
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	// ������ n-1���� �ؽ�ó���� (1) ~ (4)������ ������ �����Ͽ� �ؽ�ó�� �����Ѵ�.
	glBindTexture(GL_TEXTURE_2D, titleTex[1]);
	pBytes = LoadDIBitmap("texture/ui/logo_mask.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, titleTex[2]);
	pBytes = LoadDIBitmap("texture/ui/titleBtn.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, titleTex[3]);
	pBytes = LoadDIBitmap("texture/ui/titleBtn_mask.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);

	glBindTexture(GL_TEXTURE_2D, titleTex[4]);
	pBytes = LoadDIBitmap("texture/character/character001.bmp", &info);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, info->bmiHeader.biWidth, info->bmiHeader.biHeight, 0, GL_BGR_EXT, GL_UNSIGNED_BYTE, pBytes);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_MODULATE);
	return GLvoid();
}

GLint CRun_time_Framework::get_texture(CScene::SceneTag tag, int num)
{
	if (tag == CScene::SceneTag::Title)
		return titleTex[num];
}
