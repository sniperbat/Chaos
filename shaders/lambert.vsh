attribute highp vec4 position;
attribute mediump vec3 normal;
attribute mediump vec2 texcoord0;
attribute lowp vec4 vertexColor;

//material
uniform bool hasVertexColor;
uniform bool hasTexture;
uniform lowp vec4 diffuseColor;
uniform lowp vec4 ambientColor;
uniform lowp vec4 emissiveColor;
uniform lowp float alphaFactor;

//transform
uniform highp mat4 wvp;
uniform highp mat4 wvit;

varying lowp vec4 colorVarying;
varying mediump vec2 texCoordVarying;
varying mediump float varDot;

void main(){
  gl_Position = wvp * position;
  if( hasTexture )
    texCoordVarying = texcoord0;

  vec4 _normal = vec4( normal, 0.0);
  _normal = wvit * _normal;
  vec3 lightDir = normalize( vec3( 100.0,100.0,300.0) - position.xyz );
  _normal.xyz = normalize(_normal.xyz);
  varDot = max(dot( _normal.xyz, lightDir ), 0.0);

  vec4 baseColor = vec4(1.0,1.0,1.0,1.0);
  if( hasVertexColor )
    baseColor *= vertexColor;
  colorVarying = baseColor * diffuseColor * varDot + ambientColor + emissiveColor;
}
