#pragma once
#ifndef ES_APP_VOLUME_CONTROL_H
#define ES_APP_VOLUME_CONTROL_H

#include <memory>

#if defined (__APPLE__)
    #error TODO: Not implemented for MacOS yet!!!
#elif defined(__linux__)
	#include <unistd.h>
	#include <fcntl.h>
	#include <alsa/asoundlib.h>
#elif defined(WIN32) || defined(_WIN32)
	#include <Windows.h>
	#include <endpointvolume.h>
	#include <mmeapi.h>
#endif

/*!
Singleton pattern. Call getInstance() to get an object.
*/
class VolumeControl
{
#if defined (__APPLE__)
    #error TODO: Not implemented for MacOS yet!!!
#elif defined(__linux__)
    static std::string mixerName;
    static std::string mixerCard;
    int mixerIndex;
    snd_mixer_t* mixerHandle;
    snd_mixer_elem_t* mixerElem;
    snd_mixer_selem_id_t* mixerSelemId;
#elif defined(WIN32) || defined(_WIN32)
	HMIXER mixerHandle;
	MIXERCONTROL mixerControl;
	IAudioEndpointVolume * endpointVolume;
#endif

	int originalVolume;
	int internalVolume;

	static std::weak_ptr<VolumeControl> sInstance;

	VolumeControl();
	VolumeControl(const VolumeControl & right);
    VolumeControl & operator=(const VolumeControl & right);

	

public:
	static std::shared_ptr<VolumeControl> & getInstance();

	void init();
	void deinit();

	bool isAvailable();

	int getVolume() const;
	void setVolume(int volume);

	~VolumeControl();
};

#endif // ES_APP_VOLUME_CONTROL_H
