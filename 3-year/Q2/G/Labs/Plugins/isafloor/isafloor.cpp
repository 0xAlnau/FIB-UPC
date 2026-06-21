#include "isafloor.h"
#include "glwidget.h"

void Isafloor::onPluginLoad()
{
float areaTotal = 0.0f;
    float areaSuelo = 0.0f;
    
    vector<Object> obj = scene()->objects();
    if (obj.empty()) return; // Por seguridad, comprobar que hay objeto
    
    const vector<Face>& fac = obj[0].faces();
    const vector<Vertex>& verts = obj[0].vertices(); // Necesitamos los vértices, no solo las normales de vértice
    
    for (unsigned int i = 0; i < fac.size(); ++i) {
        // 1. Obtener las coordenadas de los 3 vértices del triángulo
        int idx0 = fac[i].vertexIndex(0);
        int idx1 = fac[i].vertexIndex(1);
        int idx2 = fac[i].vertexIndex(2);
        
        Point p0 = verts[idx0].coord();
        Point p1 = verts[idx1].coord();
        Point p2 = verts[idx2].coord();
        
        // 2. Calcular los vectores de las aristas u y v
        Vector u = p1 - p0;
        Vector v = p2 - p0;
        
        // 3. Producto vectorial para obtener el vector normal de la cara
        Vector N = Vector::crossProduct(u, v);
        
        // 4. Calcular el área usando el módulo (length) del vector normal
        float areaCara = N.length() / 2.0f;
        areaTotal += areaCara;
        
        // 5. Normalizar N para tener la normal unitaria
        Vector normalUnitaria = N.normalized();
        
        // 6. Condición: Producto escalar con (0,0,1) > 0.7
        // Como vimos, esto es directamente la componente Z
        if (normalUnitaria.z() > 0.7f) {
            areaSuelo += areaCara;
        }
    }

    // Calcular el lambda final
    if (areaTotal > 0.0f) {
        lambda = areaSuelo / areaTotal;
    } else {
        lambda = 0.0f;
    }

    // Imprimir por consola exactamente como pide el enunciado
    cout << "TERRA: " << lambda << endl;

    // Carregar shader, compile & link
    QString vs_src =
      "#version 330 core\n"
      "uniform mat4 modelViewProjectionMatrix;"
      "uniform mat3 normalMatrix;"
      "uniform float lambda;"
      "in vec3 vertex;"
      "in vec3 color;"
      "in vec3 normal;"
      "out vec4 col;"
      "void main() {"
      "  vec3 N = normalize(normalMatrix * normal);"
      "  gl_Position = modelViewProjectionMatrix * vec4(vertex,1.0);"
      "  vec3 color = mix(vec3(1.0,0.0,0.0), vec3(0.0,1.0,0.0), lambda);"
      "  col=vec4(color,1.0) * N.z;"
      "}";
    vs = new QOpenGLShader(QOpenGLShader::Vertex, this);
    vs->compileSourceCode(vs_src);
    cout << "VS log:" << vs->log().toStdString() << endl;

    QString fs_src =
      "#version 330 core\n"
      "out vec4 fragColor;"
      "in vec4 col;"
      "void main() {"
      "fragColor=col;"
      "}";
    fs = new QOpenGLShader(QOpenGLShader::Fragment, this);
    fs->compileSourceCode(fs_src);
    cout << "FS log:" << fs->log().toStdString() << endl;

    program = new QOpenGLShaderProgram(this);
    program->addShader(vs);
    program->addShader(fs);
    program->link();
    cout << "Link log:" << program->log().toStdString() << endl;	
}

void Isafloor::preFrame()
{
    program->bind(); //activem

    QMatrix4x4 MVP = camera()->projectionMatrix() * camera()->viewMatrix();
    program->setUniformValue("modelViewProjectionMatrix", MVP);
    
    QMatrix3x3 NM = camera()->viewMatrix().normalMatrix(); //qt ens fa el calcul de normalMatrix
    program->setUniformValue("normalMatrix", NM);
    
    program->setUniformValue("lambda", lambda);
}


