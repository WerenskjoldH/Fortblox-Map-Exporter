#pragma once

#include <fstream>
#include <iostream>

#include <zlib.h>

typedef unsigned __int8 u_int8;

struct vec3f {
	float x = 0.f;
	float y = 0.f;
	float z = 0.f;
};

struct vec2f {
	float pitch = 0.f;
	float yaw = 0.f;
};

class fortBloxMapInfo {
private:

public:
	__int32 spawnCount;
	__int32 m_sizex;
	__int32 m_sizey;
	__int32 m_sizez;

	u_int8* data;
	vec3f* spawnPos;
	vec2f* spawnTilt;

	
	fortBloxMapInfo() {};
	fortBloxMapInfo(__int32 mapX, __int32 mapY, __int32 mapZ, __int32 iSpawnCount) : m_sizex(mapX), m_sizey(mapY), m_sizez(mapZ), spawnCount(iSpawnCount)
	{
		spawnPos = (vec3f*)malloc(iSpawnCount * sizeof(vec3f));
		spawnTilt = (vec2f*)malloc(iSpawnCount * sizeof(vec2f));

		data = (u_int8*)malloc(mapX * mapY * mapZ * sizeof(u_int8));
		for (int i = 0; i < mapX * mapY * mapZ; i++)
			data[i] = 0;
	}

	void outputMap()
	{
		gzFile file;

		if ((file = gzopen("newMap.map", "wb")) == NULL)
		{
			std::cout << "Error opening file" << std::endl;

			exit(-1);
		}


		gzwrite(file, &m_sizex, sizeof(__int32));
		gzwrite(file, &m_sizey, sizeof(__int32));
		gzwrite(file, &m_sizez, sizeof(__int32));

		gzwrite(file, &spawnCount, sizeof(__int32));

		for(int i = 0; i < m_sizex * m_sizey * m_sizez; i++)
			gzwrite(file, &data[i], sizeof(u_int8));

		for (int i = 0; i < spawnCount; i++)
		{
			gzwrite(file, &spawnPos[i].x, sizeof(float));
			gzwrite(file, &spawnPos[i].y, sizeof(float));
			gzwrite(file, &spawnPos[i].z, sizeof(float));

			gzwrite(file, &spawnTilt[i].pitch, sizeof(float));
			gzwrite(file, &spawnTilt[i].yaw, sizeof(float));
		}

		gzclose(file);
	}
};

