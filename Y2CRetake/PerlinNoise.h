#include <vector>
#include "BasicLayout.h"
class PerlinNoise {
// The permutation vector
public:
	// Initialize with the reference values for the permutation vector
	PerlinNoise() = default;
	// Generate a new permutation vector based on the value of seed
	PerlinNoise(unsigned int seed);
	// Get a noise value, for 2D images z can have any value
	double noise(double x, double y, double z);
	//Actually generate the map
	void GenerateNoiseMap(std::vector<ETILE_TYPE>& a_Tiles, int a_Width, int a_Height);

	std::vector<int> p;

private:
	double fade(double t);
	double lerp(double t, double a, double b);
	double grad(int hash, double x, double y, double z);
};