#version 330 core

// +++++++++++++++++++++++++++++++++++++++++

// Solar System constants (Sun + 8 planets)
// Some data approximated from NASA Planetary Fact Sheet

const int NUM_BODIES = 9;  // Sun + 8 planets
const int NUM_VERTS_SPHERE = 960;
const float TIME_SCALE = 1e7;

// fake radii
const float bodyRadii[NUM_BODIES] = float[NUM_BODIES](
    1.6,  // Sun
    0.3,  // Mercury
    0.5,  // Venus
    0.5,  // Earth
    0.3,  // Mars
    1.3,  // Jupiter
    1.2,  // Saturn
    0.7,  // Uranus
    0.7   // Neptune
);


// Rotational angular speeds (radians/second)
const float bodyRotAngularSpeed[NUM_BODIES] = float[NUM_BODIES](
    2.0 * 3.1415926 / (25.05 * 86400.0),    // Sun (~25 Earth days at equator)
    2.0 * 3.1415926 / (58.646 * 86400.0),   // Mercury
    -2.0 * 3.1415926 / (243.025 * 86400.0), // Venus (retrograde)
    2.0 * 3.1415926 / (0.997 * 86400.0),    // Earth
    2.0 * 3.1415926 / (1.026 * 86400.0),    // Mars
    2.0 * 3.1415926 / (0.4135 * 86400.0),   // Jupiter
    2.0 * 3.1415926 / (0.444 * 86400.0),    // Saturn
    -2.0 * 3.1415926 / (0.718 * 86400.0),   // Uranus (retrograde)
    2.0 * 3.1415926 / (0.671 * 86400.0)     // Neptune
);

// Orbital angular speeds (radians/second)
const float bodyOrbitalAngularSpeed[NUM_BODIES] = float[NUM_BODIES](
    0.0,                                      // Sun (stationary at center)
    2.0 * 3.1415926 / (87.97 * 86400.0),     // Mercury
    2.0 * 3.1415926 / (224.70 * 86400.0),    // Venus
    2.0 * 3.1415926 / (365.256 * 86400.0),   // Earth
    2.0 * 3.1415926 / (686.98 * 86400.0),    // Mars
    2.0 * 3.1415926 / (4332.59 * 86400.0),   // Jupiter
    2.0 * 3.1415926 / (10759.22 * 86400.0),  // Saturn
    2.0 * 3.1415926 / (30688.5 * 86400.0),   // Uranus
    2.0 * 3.1415926 / (60182.0 * 86400.0)    // Neptune
);

// Fake orbital distances from the Sun
const float bodySunDistance[NUM_BODIES] = float[NUM_BODIES](
    0.0,   // Sun
    3.2,   // Mercury
    4.0,   // Venus
    5.0,   // Earth
    6.2,   // Mars
    8.0,   // Jupiter
    12.0,  // Saturn
    17.0,  // Uranus
    24.0   // Neptune
);

// RGB colors
const vec3 bodyColors[NUM_BODIES] = vec3[NUM_BODIES](
    vec3(1.0, 0.9, 0.6),   // Sun  bright yellow-white
    vec3(0.5, 0.5, 0.5),   // Mercury  gray
    vec3(0.9, 0.8, 0.6),   // Venus  pale yellow
    vec3(0.2, 0.4, 1.0),   // Earth  blue oceans + white clouds
    vec3(0.8, 0.4, 0.3),   // Mars  reddish
    vec3(0.9, 0.8, 0.6),   // Jupiter  light tan/orange
    vec3(0.8, 0.7, 0.5),   // Saturn  pale yellow/beige
    vec3(0.6, 0.8, 0.9),   // Uranus  light blue-green
    vec3(0.4, 0.6, 0.9)    // Neptune  deep blue
);


// +++++++++++++++++++++++++++++++++++++++++

layout (location = 0) in vec3 vertex;
layout (location = 1) in vec3 normal;
layout (location = 2) in vec3 color;
layout (location = 3) in vec2 texCoord;

out vec4 frontColor;
out vec2 vtexCoord;

uniform mat4 modelViewProjectionMatrix;
uniform mat4 modelMatrix;
uniform mat3 normalMatrix;
uniform float time;

uniform vec4 lightAmbient;
uniform vec4 lightDiffuse;
uniform vec4 lightSpecular;
uniform vec4 lightPosition;

 // (sempre estarà en eye space)
uniform vec4 matAmbient;
uniform vec4 matDiffuse;
uniform vec4 matSpecular;
uniform float matShininess;

uniform mat4 modelViewMatrix;
uniform mat4 viewMatrix;

int id;

void main()
{
    int vertID = gl_VertexID;
    id = 0;
    if (0 <= vertID && vertID <= NUM_VERTS_SPHERE - 1) id = 0;
    else if (NUM_VERTS_SPHERE <= vertID && vertID <= 2*NUM_VERTS_SPHERE - 1) id = 1;
    else if (2*NUM_VERTS_SPHERE <= vertID && vertID <= 3*NUM_VERTS_SPHERE - 1) id = 2;
    else if (3*NUM_VERTS_SPHERE <= vertID && vertID <= 4*NUM_VERTS_SPHERE - 1) id = 3;
    else if (4*NUM_VERTS_SPHERE <= vertID && vertID <= 5*NUM_VERTS_SPHERE - 1) id = 4;
    else if (5*NUM_VERTS_SPHERE <= vertID && vertID <= 6*NUM_VERTS_SPHERE - 1) id = 5;
    else if (6*NUM_VERTS_SPHERE <= vertID && vertID <= 7*NUM_VERTS_SPHERE - 1) id = 6;
    else if (7*NUM_VERTS_SPHERE <= vertID && vertID <= 8*NUM_VERTS_SPHERE - 1) id = 7;
    else id = 8;

    mat4 trans1 = mat4(vec4(1.0,0.0,0.0,0.0), vec4(0.0,1.0,0.0,0.0), vec4(0.0,0.0,1.0,0.0), vec4(-4.0*id, 0.0, 0.0, 1.0));

    mat4 scale1 = mat4(vec4(bodyRadii[id],0.0,0.0,0.0), vec4(0.0,bodyRadii[id], 0.0, 0.0), vec4(0.0, 0.0, bodyRadii[id], 0.0), vec4(0.0,0.0,0.0,1.0));

    mat4 trans2 = mat4(vec4(1.0,0.0,0.0,0.0), vec4(0.0,1.0,0.0,0.0), vec4(0.0,0.0,1.0,0.0), vec4(bodySunDistance[id], 0.0, 0.0, 1.0));

    float angle = time * bodyOrbitalAngularSpeed[id] * TIME_SCALE;

    mat4 rotY = mat4(vec4(cos(angle), 0.0, -sin(angle), 0.0), vec4(0.0, 1.0, 0.0, 0.0), vec4(sin(angle), 0.0, cos(angle), 0.0), vec4(0.0, 0.0, 0.0, 1.0));

    mat4 trans3 = mat4(vec4(1.0,0.0,0.0,0.0), vec4(0.0,1.0,0.0,0.0), vec4(0.0,0.0,1.0,0.0), vec4(16.0, 0.0, 0.0, 1.0));

    //llum worldSpace
    vec3 P_wor = (modelMatrix * vec4(vertex,1.0)).xyz;
    vec3 obs_wor = (modelMatrix * vec4(vec3(16.0, 0.0, 0.0), 1.0)).xyz;
    vec3 L = normalize(obs_wor-P_wor);
    vec3 N = normalize(mat3(modelMatrix) * normal);

    float NdotL;
    if (id == 0) NdotL = 1.0;
    else NdotL = max( 0.0, dot( N,L ) );

    frontColor = vec4(bodyColors[id], 1.0) * NdotL;


    gl_Position = modelViewProjectionMatrix * trans3 * rotY * trans2 * scale1 * trans1 * vec4(vertex, 1.0);
}
