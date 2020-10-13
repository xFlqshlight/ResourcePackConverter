#pragma once
#include "Common.h"

struct ImageProcessorSizes {
	int cubemapSize, cubemapPieceX, cubemapPieceY;
	int widgetsSize, widgetUVSize, widgetCutOutSize;
	int potionEffectSize, potionEffectUVSize;
	int expBarSize, expBarWidgetSize;
	int breakingAnimSize, breakingAnimUVSize;
	int imageSize;
};

class ImageProcessor {
private:
	enum class type {
		CUBEMAP_PIECE,
		WIDGET,
		EXP_BAR,
		POTION_EFFECT,
		BREAKING_ANIM
	};
public:
	int getImageSize();
	void calculatePieceSize(const int& imgSize, type _Type);
	void calculateWidgetSize(const int& imgSize, type _Type);
};