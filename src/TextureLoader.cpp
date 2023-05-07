#include "TextureLoader.h"

#ifndef STB_IMAGE_IMPLEMENTATION
#define STB_IMAGE_IMPLEMENTATION   

using namespace std;

#include "stb_image.h"

TextureLoader& TextureLoader::instance()
{
	static TextureLoader instance;
	return instance;
}

GLuint TextureLoader::loadTexture(std::string filename)
{
	GLuint m_textureID;
	int m_Width, m_Height, m_Channels;
  
	unsigned char* image = stbi_load(filename.c_str(), &m_Width, &m_Height, &m_Channels, 0);

	if (image)
	{
		m_Error = 0;
		//addlog("Loading: " + filename);
		printf("loading: %s \n", filename.c_str());
		
		glGenTextures(1, &m_textureID);
		glBindTexture(GL_TEXTURE_2D, m_textureID);
				
		//	Old standard texture mapping style
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_LOD_BIAS, -1.4f);		
			
		GLuint format = 0;

		switch (m_Channels)
		{
		case 1: format = GL_ALPHA;     break;
		//case 2: format = GL_LUMINANCE; break;
		case 3: format = GL_RGB;       break;
		case 4: format = GL_RGBA;      break;
		}
		
		tWidth = m_Width;
		tHeight = m_Height;
		tChannels = format;

		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0, format, GL_UNSIGNED_BYTE, image);
		glGenerateMipmap(GL_TEXTURE_2D);
		glBindTexture(GL_TEXTURE_2D, 0);

		stbi_image_free(image);
		//printf(" ID: %i \n", m_textureID);  
	return m_textureID;;		
	}
	else
	{		
		m_Error = -1;		
	}

	
}

// Loads a cubemap texture from 6 individual texture faces
// Order should be:
// +X (right)
// -X (left)
// +Y (top)
// -Y (bottom)
// +Z (front)? (CHECK THIS)
// -Z (back)?

static const GLenum GL_TEXTURE_CUBE_MAP_TYPES[6] =
                    {
                            GL_TEXTURE_CUBE_MAP_POSITIVE_X,
                            GL_TEXTURE_CUBE_MAP_NEGATIVE_X,
                            GL_TEXTURE_CUBE_MAP_POSITIVE_Y,
                            GL_TEXTURE_CUBE_MAP_NEGATIVE_Y,
                            GL_TEXTURE_CUBE_MAP_POSITIVE_Z,
                            GL_TEXTURE_CUBE_MAP_NEGATIVE_Z,
                    };


GLuint  TextureLoader::loadCubemap(string path, string extension)
{
  GLuint textureID;
  glGenTextures(1, &textureID);
  //glActiveTexture(GL_TEXTURE0);  
  std::vector<string> faces;

  // This makes the image right-way up in OpenGL
  //stbi_set_flip_vertically_on_load(true);
    faces.push_back(path + "right" + "." + extension);
    faces.push_back(path + "left" + "." + extension);
    faces.push_back(path + "top" + "."+ extension);
    faces.push_back(path + "bottom" + "." + extension);
    faces.push_back(path + "back" + "." + extension);
    faces.push_back(path + "front" + "." + extension);   

  glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);
    
    for (unsigned i = 0; i < 6; ++i){
        int w, h, bytesPerPixel;
        unsigned char*  data = stbi_load((faces[i].c_str()), &w, &h, &bytesPerPixel, 4);

        if(data == NULL){
            //LOG_ERROR_INFO("CubeMap(Texture)", "Failed to load Texture from file", m_fileNames[i]);
	  printf("Error loading: %s \n", faces[i].c_str());
	  //addlog("Error loading: " + faces[i]);
        }
        
        glTexImage2D(GL_TEXTURE_CUBE_MAP_TYPES[i], 0, GL_RGB, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
	//addlog("Loading: " + faces[i]);
	printf("Loading: %s \n", faces[i].c_str());
        stbi_image_free(data);
    }   
    
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
    glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    
    return textureID;
}

#endif














