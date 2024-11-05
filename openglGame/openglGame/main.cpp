#include <fstream> 
#include <iostream>

//#include <glad/glad.h>
//#include <GLFW/glfw3.h>
//

//#include "glm/glm.hpp"
//#include "glm/gtc/matrix_transform.hpp"
//#include "glm/gtc/type_ptr.hpp"
//
//#define STB_IMAGE_IMPLEMENTATION
//#include "stb_image.h"


#include <game.h>



int main()
{
	Game game = Game();

	if (game.Init())
	{
		return 0;
	};

	printf("test");


	return 1;
}

