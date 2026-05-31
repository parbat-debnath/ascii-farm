#include "audio.h"
#include <windows.h>
#include <mmsystem.h>
#include <stdio.h>
#include <string.h>

#pragma comment(lib, "winmm.lib")

#define MUSIC_REL_PATH     "assets/music/background.wav"
#define BUY_SFX_REL_PATH   "assets/music/buy.wav"
#define PLANT_SFX_REL_PATH "assets/music/plant.wav"
#define HARVEST_SFX_REL_PATH "assets/music/harvest.wav"

static char g_baseDir[MAX_PATH];
static int g_baseDirReady = 0;

static void sendMci(const char *command)
{
    MCIERROR err = mciSendStringA(command, NULL, 0, NULL);
    if (err != 0)
    {
        char errorText[256];
        mciGetErrorStringA(err, errorText, sizeof(errorText));
        printf("MCI error: %s\nCommand: %s\n", errorText, command);
    }
}

static void getBaseDir(void)
{
    if (g_baseDirReady)
        return;

    DWORD len = GetModuleFileNameA(NULL, g_baseDir, MAX_PATH);
    if (len == 0 || len >= MAX_PATH)
    {
        strcpy(g_baseDir, "");
        g_baseDirReady = 1;
        return;
    }

    char *lastSlash = strrchr(g_baseDir, '\\');
    if (lastSlash)
        *(lastSlash + 1) = '\0';
    else
        strcpy(g_baseDir, "");

    g_baseDirReady = 1;
}

static void makeFullPath(char *out, size_t outSize, const char *relativePath)
{
    getBaseDir();
    snprintf(out, outSize, "%s%s", g_baseDir, relativePath);
}

static void openAudioFile(const char *alias, const char *relativePath)
{
    char fullPath[MAX_PATH];
    char command[512];

    makeFullPath(fullPath, sizeof(fullPath), relativePath);

    snprintf(command, sizeof(command),
             "open \"%s\" type waveaudio alias %s",
             fullPath, alias);

    sendMci(command);
}

void initAudio(void)
{
    openAudioFile("music", MUSIC_REL_PATH);
    openAudioFile("sfx_buy", BUY_SFX_REL_PATH);
    openAudioFile("sfx_harvest", HARVEST_SFX_REL_PATH);
}

void playMusic(void)
{
    sendMci("seek music to start");
    sendMci("play music repeat");
}

void stopMusic(void)
{
    sendMci("stop music");
}

void playBuySfx(void)
{
    sendMci("seek sfx_buy to start");
    sendMci("play sfx_buy");
}

void playPlantSfx(void)
{
    sendMci("seek sfx_plant to start");
    sendMci("play sfx_plant");
}

void playHarvestSfx(void)
{
    sendMci("seek sfx_harvest to start");
    sendMci("play sfx_harvest");
}

void shutdownAudio(void)
{
    sendMci("stop music");
    sendMci("close music");

    sendMci("close sfx_buy");
    sendMci("close sfx_plant");
    sendMci("close sfx_harvest");
}