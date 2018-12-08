#include "stdafx.h"
#include "Run_Time_Framework.h"

GLvoid CRun_time_Framework::init_sound()
{
	FMOD_System_Create(&pFmod);
	FMOD_System_Init(pFmod, 10, FMOD_INIT_NORMAL, NULL);

	load_bgm();
	load_fx();
	load_voice();
}

GLvoid CRun_time_Framework::load_bgm()
{
	FMOD_System_CreateSound(pFmod, "sound/bgm/BgmHome.wav", FMOD_DEFAULT, NULL, &BGM[0]);
	FMOD_System_CreateSound(pFmod, "sound/bgm/BgmPuzzleNormal.wav", FMOD_DEFAULT, NULL, &BGM[1]);
	FMOD_System_CreateSound(pFmod, "sound/bgm/BgmPuzzleLoop.wav", FMOD_DEFAULT, NULL, &BGM[2]);
	FMOD_System_CreateSound(pFmod, "sound/bgm/BgmPuzzleShowtime.wav", FMOD_DEFAULT, NULL, &BGM[3]);
	FMOD_System_CreateSound(pFmod, "sound/bgm/BgmResult.wav", FMOD_DEFAULT, NULL, &BGM[4]);
	return GLvoid();
}

GLvoid CRun_time_Framework::set_bgm(int id)
{
	FMOD_Channel_Stop(ch[0]);
	FMOD_System_PlaySound(pFmod, BGM[id], NULL, false, &ch[0]);
	FMOD_Channel_SetVolume(ch[0], 0.3);
	FMOD_Sound_GetLength(BGM[id], length, FMOD_TIMEUNIT_MS);
	switch (id) {
	case 1:
		NowPlaying = PlayBGM::normal;
		break;
	}
}

GLvoid CRun_time_Framework::load_fx()
{
	FMOD_System_CreateSound(pFmod, "sound/fx/BtnClick.wav", FMOD_LOOP_OFF, NULL, &FX[0]);
	FMOD_System_CreateSound(pFmod, "sound/fx/CharChange.wav", FMOD_LOOP_OFF, NULL, &FX[1]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Coin01.wav", FMOD_LOOP_OFF, NULL, &FX[2]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Coin02.wav", FMOD_LOOP_OFF, NULL, &FX[3]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Coin03.wav", FMOD_LOOP_OFF, NULL, &FX[4]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Coin04.wav", FMOD_LOOP_OFF, NULL, &FX[5]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Coin05.wav", FMOD_LOOP_OFF, NULL, &FX[6]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Coin06.wav", FMOD_LOOP_OFF, NULL, &FX[7]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Coin07.wav", FMOD_LOOP_OFF, NULL, &FX[8]);
	FMOD_System_CreateSound(pFmod, "sound/fx/Jump.wav", FMOD_LOOP_OFF, NULL, &FX[9]);
	return GLvoid();
}

GLvoid CRun_time_Framework::play_fx(int id)
{
	FMOD_System_PlaySound(pFmod, FX[id], NULL, false, &ch[1]);
	return GLvoid();
}

GLvoid CRun_time_Framework::load_voice()
{
	FMOD_RESULT k;
	// 치카
	{

		FMOD_System_CreateSound(pFmod, "sound/voice/chika/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[chika][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/chika/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[chika][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/chika/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[chika][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/chika/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[chika][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/chika/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[chika][4]);
		k = FMOD_System_CreateSound(pFmod, "sound/voice/chika/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[chika][5]);
	}
	// 요우
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/you/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[you][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/you/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[you][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/you/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[you][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/you/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[you][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/you/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[you][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/you/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[you][5]);
	}
	// 리코
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/riko/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[riko][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/riko/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[riko][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/riko/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[riko][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/riko/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[riko][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/riko/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[riko][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/riko/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[riko][5]);
	}
	// 하나마루
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/hanamaru/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[hanamaru][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/hanamaru/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[hanamaru][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/hanamaru/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[hanamaru][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/hanamaru/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[hanamaru][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/hanamaru/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[hanamaru][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/hanamaru/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[hanamaru][5]);
	}
	// 루비
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/ruby/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[ruby][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/ruby/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[ruby][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/ruby/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[ruby][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/ruby/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[ruby][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/ruby/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[ruby][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/ruby/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[ruby][5]);
	}
	// 요시코
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/yoshiko/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[yoshiko][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/yoshiko/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[yoshiko][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/yoshiko/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[yoshiko][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/yoshiko/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[yoshiko][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/yoshiko/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[yoshiko][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/yoshiko/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[yoshiko][5]);
	}
	// 다이아
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/dia/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[dia][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/dia/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[dia][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/dia/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[dia][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/dia/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[dia][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/dia/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[dia][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/dia/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[dia][5]);
	}
	// 카난
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/kanan/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[kanan][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/kanan/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[kanan][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/kanan/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[kanan][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/kanan/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[kanan][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/kanan/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[kanan][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/kanan/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[kanan][5]);
	}
	// 마리
	{
		FMOD_System_CreateSound(pFmod, "sound/voice/mari/CvGameStart.wav", FMOD_LOOP_OFF, NULL, &VOICE[mari][0]);
		FMOD_System_CreateSound(pFmod, "sound/voice/mari/CvGoldA.wav", FMOD_LOOP_OFF, NULL, &VOICE[mari][1]);
		FMOD_System_CreateSound(pFmod, "sound/voice/mari/CvGoldB.wav", FMOD_LOOP_OFF, NULL, &VOICE[mari][2]);
		FMOD_System_CreateSound(pFmod, "sound/voice/mari/CvGoldC.wav", FMOD_LOOP_OFF, NULL, &VOICE[mari][3]);
		FMOD_System_CreateSound(pFmod, "sound/voice/mari/CvGoldD.wav", FMOD_LOOP_OFF, NULL, &VOICE[mari][4]);
		FMOD_System_CreateSound(pFmod, "sound/voice/mari/CvGoldLoop.wav", FMOD_LOOP_OFF, NULL, &VOICE[mari][5]);
	}

	return GLvoid();
}

GLvoid CRun_time_Framework::play_voice(int charid, int voiceid)
{
	FMOD_System_PlaySound(pFmod, VOICE[charid][voiceid], NULL, false, &ch[2]);
	return GLvoid();
}