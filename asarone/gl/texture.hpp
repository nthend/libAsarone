#ifndef TEXTURE_HPP
#define TEXTURE_HPP

#include<SDL2/SDL.h>
#include<GL/glew.h>

class Texture
{
private:
	GLuint id;
public:
	Texture()
	{
		glGenTextures(1,&id);
	}
	Texture(GLuint tex)
	{
		id = tex;
	}
	virtual ~Texture()
	{
		glDeleteTextures(1,&id);
	}

	void loadFromFile(const char *addr)
	{
		bind();

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

		SDL_Surface *face = SDL_LoadBMP(addr);
		if(face != nullptr)
		{
			glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, face->w, face->h, 0, GL_RGB, GL_UNSIGNED_BYTE, face->pixels);
			SDL_FreeSurface(face);
		}

		unbind();
	}
	void bind() const
	{
		glBindTexture(GL_TEXTURE_2D, id);
	}
	void unbind() const
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
};

#endif // TEXTURE_HPP