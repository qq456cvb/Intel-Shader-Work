#include "qtopengl.h"

#include <iostream>
#include <QtGui/QGuiApplication>
#include <QtGui/QMatrix4x4>
#include <QtGui/QOpenGLShaderProgram>
#include <QtGui/QScreen>
#include <QImageReader>
#include <QTime>

#include <QtCore/qmath.h>

class TriangleWindow : public OpenGLWindow
{
public:
	TriangleWindow();
	~TriangleWindow() { delete[] m_image; };

	void initialize() Q_DECL_OVERRIDE;
	void render() Q_DECL_OVERRIDE;
	void loadFile(const QString &fileName);

private:
	
	GLuint loadShader(GLenum type, const char *source);

	GLuint m_posAttr;
	GLuint m_colAttr;
	GLuint m_matrixUniform;
	GLuint m_texUniform;
	GLuint m_tex;

	QOpenGLShaderProgram *m_program;
	int m_frame;
	uchar *m_image;
};

TriangleWindow::TriangleWindow()
	: m_program(0)
	, m_frame(0),
	m_tex(0)
{
}


void TriangleWindow::loadFile(const QString &fileName)
{
	QImageReader reader(fileName);
	reader.setAutoTransform(true);
	QImage image = reader.read();
	image = image.convertToFormat(QImage::Format_RGBA8888);
	if (!image.isNull()) {
		int count = image.byteCount();
		m_image = new uchar[image.byteCount()];
		memcpy(m_image, image.bits(), image.byteCount());
	}
}

int main(int argc, char **argv)
{
	QGuiApplication app(argc, argv);

	QSurfaceFormat format;
	format.setSamples(16);

	TriangleWindow window;
	window.loadFile("C:\\Users\\Neil\\Desktop\\test2.jpg");

	window.setFormat(format);
	window.resize(1920, 1080);
	window.show();

	window.setAnimating(true);

	return app.exec();
}

static const char *vertexShaderSource =
"attribute highp vec4 posAttr;\n"
"void main() {\n"
"   gl_Position = posAttr;\n"
"}\n";

static const char *fragmentShaderSource =
"uniform sampler2D tex;\n"
"void main() {\n"
"   vec2 coord = gl_FragCoord.xy;\n"
"   coord.x /= 1920.0;\n"
"   coord.y /= 1080.0;\n"
"   gl_FragColor=texture(tex, coord);\n"
"}\n";

GLuint TriangleWindow::loadShader(GLenum type, const char *source)
{
	GLuint shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, 0);
	glCompileShader(shader);
	return shader;
}

void TriangleWindow::initialize()
{
	if (!m_tex)
	{
		glGenTextures(1, &m_tex);
	}
	m_program = new QOpenGLShaderProgram(this);
	m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
	m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
	m_program->link();
	m_posAttr = m_program->attributeLocation("posAttr");
	m_colAttr = m_program->attributeLocation("colAttr");
	m_matrixUniform = m_program->uniformLocation("matrix");
	m_texUniform = m_program->uniformLocation("tex");
}

void TriangleWindow::render()
{
	const qreal retinaScale = devicePixelRatio();
	glViewport(0, 0, width() * retinaScale, height() * retinaScale);

	glClear(GL_COLOR_BUFFER_BIT);
	m_program->bind();
	
	glBindTexture(GL_TEXTURE_2D, m_tex);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, 1920*2, 1080*2, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, m_tex);
	
	m_program->setUniformValue(m_texUniform, 0);

	GLfloat vertices[] = {
		-1.0f, -1.0f,
		1.0f, -1.0f,
		-1.0f, 1.0f,
		-1.0f, 1.0f,
		1.0f, 1.0f,
		1.0f, -1.0f,
	};

	GLfloat colors[] = {
		1.0f, 0.0f, 0.0f,
		0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 1.0f
	};

	glVertexAttribPointer(m_posAttr, 2, GL_FLOAT, GL_FALSE, 0, vertices);

	glEnableVertexAttribArray(0);

	glDrawArrays(GL_TRIANGLES, 0, 6);

	glDisableVertexAttribArray(0);
	glBindTexture(GL_TEXTURE_2D, 0);

	m_program->release();

	std::cout << screen()->refreshRate() << std::endl;
	++m_frame;
}