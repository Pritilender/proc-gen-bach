#include "includes.h"

// System Headers
#include <glad/glad.h>
#include <GLFW/glfw3.h>

// Standard Headers
#include <cstdio>
#include <cstdlib>

class Application
{
	public:
		Application();

		bool initialize(int, int);
		void run();

	private:
		GLFWwindow* window_;
};

