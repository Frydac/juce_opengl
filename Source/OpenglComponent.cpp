/*
  ==============================================================================

    OpenglComponent.cpp
    Created: 15 Aug 2014 1:29:57pm
    Author:  Emile

  ==============================================================================
*/

#include <GL/glew.h>
#include "../JuceLibraryCode/JuceHeader.h"
#include "OpenglComponent.h"
#include "windows.h"
#include <math.h>

//void glClearBufferfv = (void)OpenGLHelpers::getExtensionFunction("glClearBufferfv");

//==============================================================================
OpenglComponent::OpenglComponent()
{
    // In your constructor, you should add any child components, and
    // initialise any special settings that your component needs.
	
	//MainAppWindow::getMainAppWindow()->setRenderingEngine(0);
	
	setOpaque(true);

	openGLContext.setRenderer(this);
	openGLContext.attachTo(*this);
	openGLContext.setContinuousRepainting(true);

	AllocConsole();
	freopen("CONIN$", "r", stdin);
	freopen("CONOUT$", "w", stdout);
	freopen("CONOUT$", "w", stderr);




}

OpenglComponent::~OpenglComponent()
{
	openGLContext.detach();
}

void OpenglComponent::paint (Graphics& g)
{
    /* This demo code just fills the component's background and
       draws some placeholder text to get you started.

       You should replace everything in this method with your own
       drawing code..
    */

    //g.fillAll (Colours::white);   // clear the background

    //g.setColour (Colours::grey);
    //g.drawRect (getLocalBounds(), 1);   // draw an outline around the component

    //g.setColour (Colours::lightblue);
    //g.setFont (14.0f);
    //g.drawText ("OpenglComponent", getLocalBounds(),
    //            Justification::centred, true);   // draw some placeholder text
}

void OpenglComponent::resized()
{
	//this->setSize(this->getParentComponent()->getWidth(), this->getParentComponent()->getHeight());
    // This method is where you should set the bounds of any child
    // components that your component contains..

}

void OpenglComponent::newOpenGLContextCreated()
{
	//glGetString​(GL_VERSION​);
	//const GLubyte *test;
	//test = glGetString(GL_VERSION);
	//test = glGetString(GL_RENDERER);
	//test = glGetString(GL_SHADING_LANGUAGE_VERSION);

	glewInit();

	rendering_program = compile_shaders();
	glGenVertexArrays(1, &vertex_array_object);
	glBindVertexArray(vertex_array_object);

}

void OpenglComponent::renderOpenGL()
{
	jassert(OpenGLHelpers::isContextActive());

	float sinus = (float)sin(my_time.getMillisecondCounter() / 1373.0f);
	float cosine = (float)cos(my_time.getMillisecondCounter() / 4139.3f);
	float sum = sinus * .5f - cosine * .5f;
	const GLfloat red[] = { sinus * .5f + .5f, cosine * .5f + .5f, sum * .5f + .5f, 1.0f };
	glClearBufferfv(GL_COLOR, 0, red);

	// Use the program object we created earlier for rendering
	glUseProgram(rendering_program);
	// Draw one point
	glDrawArrays(GL_POINTS, 0, 1);
	glPointSize(40.0f);

}

void OpenglComponent::openGLContextClosing()
{
	glDeleteVertexArrays(1, &vertex_array_object);
	glDeleteProgram(rendering_program);
	glDeleteVertexArrays(1, &vertex_array_object);

}


GLuint OpenglComponent::compile_shaders()
{
	GLuint vertex_shader;
	GLuint fragment_shader;
	GLuint program;

	static const char * vertex_shader_source[] =
	{
		"#version 430 core \n"
		"void main(void)    \n"
		"{\n"
		"gl_Position = vec4(0.0, 0.0, 0.5, 1.0);\n"
		"}\n"
	};

	static const char * fragment_shader_source[] =
	{
		"#version 430 core \n"
		"out vec4 color; \n"
		"void main(void) \n"
		"{ \n"
		" color = vec4(0.0, 0.8, 1.0, 1.0); \n"
		"} \n"

	};

    //Create and compile vertex shader
	vertex_shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertex_shader, 1, vertex_shader_source, nullptr);
	glCompileShader(vertex_shader);

	fragment_shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragment_shader, 1, fragment_shader_source, nullptr);
	glCompileShader(fragment_shader);

	program = glCreateProgram();
	glAttachShader(program, vertex_shader);
	glAttachShader(program, fragment_shader);
	glLinkProgram(program);

    // Delete the shaders as the program has them now
	glDeleteShader(vertex_shader);
	glDeleteShader(fragment_shader);

	return program;
}
