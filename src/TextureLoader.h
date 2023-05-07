#ifndef _TEXTURELOADER_H_
#define _TEXTURELOADER_H_

#include "glad.h"
#include <vector>
#include <string>

class TextureLoader
{
public:
	static TextureLoader& instance();
	GLuint loadTexture(std::string filename);	
	GLuint loadCubemap(std::string path, std::string extension);	
	GLuint cubemapTexture;
        
	int tWidth, tHeight, tChannels, m_Error;
	std::vector<std::string>logtext;
    std::vector<GLuint>texturelist;
	
private:	
	
	
	
};

#endif



