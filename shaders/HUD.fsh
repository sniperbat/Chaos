//material
uniform bool hasVertexColor;
uniform bool hasTexture;

uniform sampler2D diffuseTexture;

varying mediump vec4 colorVarying;
varying mediump vec2 texCoordVarying;

void main(){
	mediump vec4 baseColor = vec4(1.0,1.0,1.0,1.0);
	
	if( hasVertexColor ){
		baseColor *= colorVarying;
	}
	
	if( hasTexture ){
		baseColor *= texture2D( diffuseTexture, texCoordVarying.st, 0.0 );
	}
	
  gl_FragColor = baseColor;
}
