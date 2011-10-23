#include <jni.h>
#include <android/log.h>

#include <GLES2/gl2.h>
#include <GLES2/gl2ext.h>

#include "Matrix.hpp"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define  LOG_TAG    "cubedroid2"
#define  LOGI(...)  __android_log_print(ANDROID_LOG_INFO,LOG_TAG,__VA_ARGS__)
#define  LOGE(...)  __android_log_print(ANDROID_LOG_ERROR,LOG_TAG,__VA_ARGS__)

// インデックス
enum {
    ATTRIB_VERTEX,
    ATTRIB_COLOR,
    NUM_ATTRIBUTES
};

// ログ出力
static void printGLString(const char *name, GLenum s) {
    const char *v = (const char *) glGetString(s);
    LOGI("GL %s = %s\n", name, v);
}

// エラーチェックを行う
static void checkGlError(const char* op) {
    for (GLint error = glGetError(); error; error
            = glGetError()) {
        LOGI("after %s() glError (0x%x)\n", op, error);
    }
}

// 頂点シェーダ
static const char gVertexShader[] = 
    "attribute vec4 Position;      \n"
    "attribute vec4 SourceColor;   \n"
    "varying vec4 DestinationColor;\n"
    "uniform mat4 Projection;      \n"
    "uniform mat4 Modelview;       \n"
    "void main() {\n"
        "   gl_Position = Projection * Modelview * Position; \n"
        "   DestinationColor = SourceColor; \n"
    "}\n";

// フラグメントシェーダ
static const char gFragmentShader[] = 
    "varying lowp vec4 DestinationColor; \n"
    "void main() {                       \n"
    "  gl_FragColor = DestinationColor;  \n"
    "}\n";

GLuint loadShader(GLenum shaderType, const char* pSource) {
    GLuint shader = glCreateShader(shaderType);
    if (shader) {
        glShaderSource(shader, 1, &pSource, NULL);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);
        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char* buf = (char*) malloc(infoLen);
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, NULL, buf);
                    LOGE("Could not compile shader %d:\n%s\n",
                            shaderType, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

GLuint createProgram(const char* pVertexSource, const char* pFragmentSource) {

	// シェーダプログラムをロードする
    GLuint vertexShader = loadShader(GL_VERTEX_SHADER, pVertexSource);
    if (!vertexShader) {
        return 0;
    }

    GLuint pixelShader = loadShader(GL_FRAGMENT_SHADER, pFragmentSource);
    if (!pixelShader) {
        return 0;
    }

    GLuint program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShader);
        checkGlError("glAttachShader");
        glAttachShader(program, pixelShader);
        checkGlError("glAttachShader");
        glLinkProgram(program);
        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);
        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char* buf = (char*) malloc(bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, NULL, buf);
                    LOGE("Could not link program:\n%s\n", buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

GLuint gProgram;
GLuint gWidth;
GLuint gHeight;

// グラフィックスの設定
bool setupGraphics(int w, int h) {

    printGLString("Version", GL_VERSION);
    printGLString("Vendor", GL_VENDOR);
    printGLString("Renderer", GL_RENDERER);
    printGLString("Extensions", GL_EXTENSIONS);

    LOGI("setupGraphics(%d, %d)", w, h);
    gProgram = createProgram(gVertexShader, gFragmentShader);
    if (!gProgram) {
        LOGE("Could not create program.");
        return false;
    }

    // 頂点座標の設定
    glBindAttribLocation(gProgram, ATTRIB_VERTEX, "Position");
    checkGlError("glBindAttribLocation");

    // 色座標を設定
    glBindAttribLocation(gProgram, ATTRIB_COLOR, "SourceColor");
    checkGlError("glBindAttribLocation");

    glViewport(0, 0, w, h);
    checkGlError("glViewport");

    gWidth = w;
    gHeight = h;

    glUseProgram(gProgram);
    checkGlError("glUseProgram");

    // 透視変換行列の設定
    GLint projectionUniform = glGetUniformLocation(gProgram, "Projection");
    mat4 projectionMatrix = mat4::Frustum(-2.0, 2.0, -2.0 * gHeight / gWidth, 2.0 * gHeight / gWidth, 1.0f,1000);

    glEnable(GL_DEPTH_TEST);

//    mat4 projectionMatrix = mat4::Ortho(-2.0, 2.0, -2.0 * gHeight / gWidth, 2.0 * gHeight / gWidth, 1.0, 1000.0);
    glUniformMatrix4fv(projectionUniform, 1, 0, projectionMatrix.Pointer());

    return true;
}

const GLfloat cubeVertices[] = {
        -1.0, -1.0,  1.0,
         1.0, -1.0,  1.0,
        -1.0,  1.0,  1.0,
         1.0,  1.0,  1.0,
        -1.0, -1.0, -1.0,
         1.0, -1.0, -1.0,
        -1.0,  1.0, -1.0,
         1.0,  1.0, -1.0,
    };

const GLushort cubeIndices[] = {
        0, 1, 2, 3, 7, 1, 5, 4, 7, 6, 2, 4, 0, 1
};

static const GLfloat cubeColors2[] = {
    1.0, 1.0,   0, 1.0,
    0,   1.0, 1.0, 1.0,
    0,     0, 1.0, 1.0,
    1.0,   0, 1.0, 1.0,
    1.0, 1.0,   0, 1.0,
    0,   1.0, 1.0, 1.0,
    0,     0, 1.0, 1.0,
    1.0,   0, 1.0, 1.0,
};

static const GLubyte cubeColors[] = {
    255, 255,   0, 255,
    0,   255, 255, 255,
    0,     0, 255, 255,
    255,   0, 255, 255,
    255, 255,   0, 255,
    0,   255, 255, 255,
    0,     0, 255, 255,
    255,   0, 255, 255,
};

static int angle = 0, angle2=0;

//const GLfloat gTriangleVertices[] = { 1.0f, -1.0f, 0.0f,
//                                       0.0f,  1.0f, 0.0f,
//                                      -1.0f, -1.0f, 0.0f };

void renderFrame() {

    glClearColor(.7f, .7f, .9f, 1.f);
    checkGlError("glClearColor");
    glClear( GL_DEPTH_BUFFER_BIT | GL_COLOR_BUFFER_BIT);
    checkGlError("glClear");

    // 表示物の姿勢特定、行列取得
    angle = (angle + 1) % 360;
    angle2 = (angle2 + 2) % 360;
    mat4 rotationX = mat4::RotateX(angle);
    mat4 rotationY = mat4::RotateY(angle2);
    mat4 rotationZ = mat4::RotateZ(angle);
    mat4 scale = mat4::Scale(1.0);
    mat4 translation = mat4::Translate(0, 0, -3);
    mat4 modelviewMatrix =  scale * rotationX * rotationY * translation;
    
    // 表示物の姿勢設定
    int modelviewUniform = glGetUniformLocation(gProgram, "Modelview");
    glUniformMatrix4fv(modelviewUniform, 1, 0, modelviewMatrix.Pointer());

    //頂点の設定
    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, cubeVertices);
//    glVertexAttribPointer(ATTRIB_VERTEX, 3, GL_FLOAT, GL_FALSE, 0, gTriangleVertices);
//    glVertexAttribPointer(ATTRIB_COLOR, 4, GL_UNSIGNED_BYTE, GL_FALSE, 0, cubeColors);
    // 色の指定
    glVertexAttribPointer(ATTRIB_COLOR, 4, GL_FLOAT, GL_FALSE, 0, cubeColors2);
    checkGlError("glVertexAttribPointer");

    glEnableVertexAttribArray(ATTRIB_VERTEX);
    glEnableVertexAttribArray(ATTRIB_COLOR);
    checkGlError("glEnableVertexAttribArray");

//     描画する
//    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDrawElements(GL_TRIANGLE_STRIP, 14, GL_UNSIGNED_SHORT, cubeIndices);
    checkGlError("glDrawElements");

    glDisableVertexAttribArray(ATTRIB_VERTEX);
    glDisableVertexAttribArray(ATTRIB_COLOR);
}

extern "C" {
    JNIEXPORT void JNICALL Java_com_example_cubedroid2_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height);
    JNIEXPORT void JNICALL Java_com_example_cubedroid2_GL2JNILib_step(JNIEnv * env, jobject obj);
};

JNIEXPORT void JNICALL Java_com_example_cubedroid2_GL2JNILib_init(JNIEnv * env, jobject obj,  jint width, jint height)
{
    setupGraphics(width, height);
}

JNIEXPORT void JNICALL Java_com_example_cubedroid2_GL2JNILib_step(JNIEnv * env, jobject obj)
{
    renderFrame();
}
