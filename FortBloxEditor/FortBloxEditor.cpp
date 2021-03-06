#define _CRT_SECURE_NO_WARNINGS
#define ZLIB_WINAPI

#include "fortBloxMap.h"

void buildMap(fortBloxMapInfo &fbInfo)
{
	int of = 0, pf = 0, cW = fbInfo.m_sizex / 7;
	for (int x = 0; x < fbInfo.m_sizex; x++)
	{
		if (x % cW == 0)
			of = 1 - of;

		for (int z = 0; z < fbInfo.m_sizez; z++)
		{
			if (z % cW == 0)
				pf = 1 - pf;

			if (of && pf)
				for (int y = 0; y < (rand() % (fbInfo.m_sizey / 2)); y++)
					fbInfo.data[x + z * (fbInfo.m_sizex) + y * (fbInfo.m_sizex * fbInfo.m_sizez)] = (u_int8)(100);
			else
				fbInfo.data[x + z * (fbInfo.m_sizex)] = (u_int8)(50);
		}
	}

	// Only one for test purposes so...
	of = 0;
	pf = 0;
	int spwCtr = 0;
	for (int x = 1; x < fbInfo.m_sizex; x++)
	{
		if (x % cW == 0)
			of = 1 - of;

		for (int z = 1; z < fbInfo.m_sizez; z++)
		{
			if (z % cW == 0)
				pf = 1 - pf;

			if (!of && !pf)
				if ((x % cW == (cW / 2)) && z % cW == (cW / 2))
				{
					fbInfo.spawnPos[spwCtr].x = x;
					fbInfo.spawnPos[spwCtr].y = 8;
					fbInfo.spawnPos[spwCtr].z = z;

					fbInfo.spawnTilt[spwCtr].pitch = 0.f;
					fbInfo.spawnTilt[spwCtr].yaw = 0.f;

					spwCtr++;
				}

		}
	}
}

int main()
{
	// Keep map sizes as a power of 2
	fortBloxMapInfo* fbInfo = new fortBloxMapInfo(256, 128, 256, 10);

	buildMap(*fbInfo);

	fbInfo->outputMap();

	system("PAUSE");

	return 0;
}