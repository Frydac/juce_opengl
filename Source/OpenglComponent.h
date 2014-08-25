/*
  ==============================================================================

    OpenglComponent.h
    Created: 15 Aug 2014 1:29:57pm
    Author:  Emile

  ==============================================================================
*/

#ifndef OPENGLCOMPONENT_H_INCLUDED
#define OPENGLCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class OpenglComponent    : public Component, private OpenGLRenderer 
{
public:
    OpenglComponent();
    ~OpenglComponent();

    void paint (Graphics&);
    void resized();

	void newOpenGLContextCreated();
	void renderOpenGL();
	void openGLContextClosing();

private:

	GLuint compile_shaders();

	OpenGLContext openGLContext;

	Time my_time;

	GLuint rendering_program;
	GLuint vertex_array_object;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (OpenglComponent)
};


#endif  // OPENGLCOMPONENT_H_INCLUDED
