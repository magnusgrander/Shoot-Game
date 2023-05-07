#include "glad.h"

#include <iostream>
#include <map>
#include <string>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
// FreeType
#include <ft2build.h>
#include FT_FREETYPE_H
// GL includes
#ifndef __FONT2D_H__
#define __FONT2D_H__

#include "shader.h" 

/// Holds all state information relevant to a character as loaded using FreeType
struct Character {
    GLuint TextureID;   // ID handle of the glyph texture
    glm::ivec2 Size;    // Size of glyph
    glm::ivec2 Bearing;  // Offset from baseline to left/top of glyph
    GLuint Advance;    // Horizontal offset to advance to next glyph
    int charid;
};


class font2d 
{
public:    
    bool init(std::string fontname, int fontsize, int screenheight, int screenwidth);
    void RenderText(std::string text, GLfloat x, GLfloat y, GLfloat scale, glm::vec3 color); 
    int getlines(void);
    
    
private:
    std::map<GLchar, Character> Characters;
    GLuint VAO, VBO;
    GLuint fontVAO, fontVBO;
    Shader *textshader; 
    int line;
    glm::mat4 projection;
    
};

#endif
