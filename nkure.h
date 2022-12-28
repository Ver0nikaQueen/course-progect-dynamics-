#pragma once

float zapoln(float* mass, int n)
{
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < 7; j++) {
			mass[i][j] += 1;
		}
	}
	return *mass;
}
