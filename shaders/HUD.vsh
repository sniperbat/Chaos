attribute highp vec4 position;
attribute lowp vec4 vertexColor;
attribute mediump vec2 texcoord0;

//material
uniform bool hasVertexColor;
uniform bool hasTexture;

//transform
uniform highp mat4 wvp;

varying lowp vec4 colorVarying;
varying mediump vec2 texCoordVarying;

void main(){
  gl_Position = wvp * position;
	if( hasVertexColor )
		colorVarying = vertexColor;
	texCoordVarying = texcoord0;
}
