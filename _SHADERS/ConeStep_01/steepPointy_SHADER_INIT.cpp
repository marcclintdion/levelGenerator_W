     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      steepPointy_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_steepPointy =                                                                                                        

      "    #define highp                                                                                                                                                \n"                           

      "    uniform highp vec4  light_POSITION_01;                                                                                                                       \n"                           
      "    uniform       mat4  mvpMatrix;                                                                                                                               \n"                           
      "    uniform       mat4  mvMatrix;                                                                                                                                \n"        
           //-----
      "    uniform       mat4  viewMatrix;                                                                                                                              \n"                   
           //-----
      "    uniform       mat4  projectionShadow;                                                                                                                        \n"        
      "    uniform       mat4  modelViewShadow;                                                                                                                         \n"        
           //-----      
      "    uniform       mat4  lightMatrix;                                                                                                                             \n"                                                             
      "    uniform       mat4  undoMatrix;                                                                                                                              \n"     
      "    uniform       mat4  textureMatrix;                                                                                                                           \n"         
      "    uniform highp float shininess;                                                                                                                               \n"                       
      //--------------------------------------------
      "    uniform highp float quadraticAttenuation;                                                                                                                    \n"                       
      "    uniform highp float linearAttenuation;                                                                                                                       \n"  
      "    uniform highp float constantAttenuation;                                                                                                                     \n" 
      //--------------------------------------------
      "    attribute     vec4  position;                                                                                                                                \n"                           
      "    attribute     vec3  normal;                                                                                                                                  \n"         
      "    attribute     vec3  tangent;                                                                                                                                 \n"             
      "    attribute     vec2  texture;                                                                                                                                 \n"                           
      
      "    uniform highp vec4  offset;                                                                                                                                  \n" 
      "    varying highp vec4  lightPosition_PASS;                                                                                                                      \n"                           
      "    varying highp vec4  shadowTexcoord;                                                                                                                          \n"       
      
      "    varying highp vec3  PASS_tangent;                                                                                                                            \n"      
      
      "    varying highp vec2  varTexcoord;                                                                                                                             \n"                           
      "            highp vec4  TEMP_shadowTexcoord;                                                                                                                     \n" 
      //--------------------------------------------
      "    varying highp vec3  aux;                                                                                                                                     \n"       
      "    varying highp float dist;                                                                                                                                    \n" 
      "            highp vec4  ecPos;                                                                                                                                   \n" 
       
//-----------------------------------------------------------------------------------------------------------------
      "    varying highp vec3  vertex_pos;                                                                                                                              \n" 
//-----------------------------------------------------------------------------------------------------------------      
      "    mat4  ScaleMatrix = mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);                                              \n"  
  
      //========================================================================================================================== 
      "    void main()                                                                                                                                                  \n"                           
      "    {                                                                                                                                                            \n"                           
        
      "            highp vec3 eyeSpaceVert      =  highp vec3(mvMatrix * position);                                                                                     \n"
                   //----------------
      "            highp vec3 eyeSpaceNormal    =  highp vec3(mvMatrix * vec4(normal, 0.0));                                                                            \n"  
      "            highp vec3 eyeSpaceTangent   =  highp vec3(mvMatrix * vec4(tangent, 0.0));                                                                           \n"  
      "            highp vec3 eyeSpaceBinormal  =   cross(eyeSpaceNormal, eyeSpaceTangent);                                                                             \n"  
                   //---------------------------------------------------------------------------------------------------------    
      "            vertex_pos                   =   highp vec3 ( dot (eyeSpaceTangent,  eyeSpaceVert),                                                                  \n" 
      "                                                          dot (eyeSpaceBinormal, eyeSpaceVert),                                                                  \n" 
      "                                                          dot (eyeSpaceNormal,   eyeSpaceVert));                                                                 \n" 
      
                   //---------------------------------------------------------------------------------------------------------     
     
      "            TEMP_shadowTexcoord   =   ScaleMatrix * projectionShadow * modelViewShadow * viewMatrix * mvMatrix * position;                                       \n" 
//   "            TEMP_shadowTexcoord   =   TEMP_shadowTexcoord / TEMP_shadowTexcoord.w;                                                                               \n"      
      
      
      "            shadowTexcoord        =   TEMP_shadowTexcoord;                                                                                                       \n"    
                  //---------------------------------------------------------------------------------------------------------
      "            lightPosition_PASS    =   normalize(lightMatrix * light_POSITION_01);                                                                                \n"                           
                   //-------------------------------------------------------------------------
      "		       ecPos                 =   mvMatrix * position;                                                                                                   \n" //this portion comes from --> Lighthouse3d.com
      "		       aux                   =   highp vec3(ecPos - lightPosition_PASS );                                                                                     \n" //this portion comes from --> Lighthouse3d.com 
      "		       dist                  =   length(aux);                                                                                                           \n" //this portion comes from --> Lighthouse3d.com 
                   //--------------------------------------------------------  
      "            varTexcoord           =   texture;                                                                                                                   \n"                           
      "            gl_Position           =   mvpMatrix * position;                                                                                                      \n"                           

      "    }\n";                                                                                                                             
      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################        
   
   
      //---------------------------------------------------------------------                                                                   
      steepPointy_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(steepPointy_SHADER_VERTEX, 1, &vertexSource_steepPointy, NULL);                                                                        
      glCompileShader(steepPointy_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_steepPointy =                                                                                                            

      " #ifdef GL_ES                                                                                                                                                    \n"                       
      " #else                                                                                                                                                           \n"                       
      " #define highp                                                                                                                                                   \n"                       
      " #endif                                                                                                                                                          \n"                       
     
      "    uniform highp sampler2D   Texture1;                                                                                                                                \n"                       
      "    uniform highp sampler2D   NormalMap;                                                                                                                               \n"                       
      "    uniform highp sampler2D   HeightMap;                                                                                                                               \n"        
      "    uniform highp sampler2D   ShadowTexture;                                                                                                                           \n"     
      "    uniform highp float shininess;                                                                                                                               \n"                       
    //--------------------------------------------
      "    uniform highp vec4  light_POSITION_01;                                                                                                                       \n"    
      "    varying highp vec4  lightPosition_PASS;                                                                                                                      \n"                       
      //--------------------------------------------
      "    uniform highp float constantAttenuation;                                                                                                                     \n" 
      "    uniform highp float linearAttenuation;                                                                                                                       \n"  
      "    uniform highp float quadraticAttenuation;                                                                                                                    \n"                       
      //--------------------------------------------
      "    varying highp vec3  aux;                                                                                                                                     \n"       
      "    varying highp float dist;                                                                                                                                    \n" 
      //--------------------------------------------
      "    varying highp vec4  shadowTexcoord;                                                                                                                          \n"         
      "    varying highp vec2  varTexcoord;                                                                                                                             \n"                       
      //--------------------------------------------
      "    varying highp vec3 vertex_pos;                                                                                                                                \n" 
     //-------------------------
      "            highp float   NdotL2;                                                                                                                                \n"                       
      
      "            highp vec4    shadow;                                                                                                                                \n"     
        
      "            highp vec3    normal_2;                                                                                                                              \n"                       
      "            highp vec3    NormalTex;                                                                                                                             \n"                       
      //-----------------------------------
      //-----------------------------------      
      //=============================================================================================================================     
      "    highp float glAttenuation(inout highp float inOutAttenuation, in highp float distanceToLight);                                                               \n"      
      //=============================================================================================================================        
      "    void intersect_square_cone_3step (inout highp vec3 dp, in highp vec3 ds);                                                                                    \n" 
//    "    void ray_intersect_cone(inout vec3 p, inout vec3 v);                                                                                                         \n" 
//    "    void setup_ray_ps(in vec2 texCoordinates, out vec3 rayPos, out vec3 rayVec);                                                                                 \n"       
      //=============================================================================================================================     

      "     void main()                                                                                                                                                 \n"                       
      "     {                                                                                                                                                           \n"                       
   
      "              highp vec3 s;                                                                                                                                            \n"
      "              highp vec3 pt_eye;                                                                                                                                       \n"
      "              highp float a;                                                                                                                                           \n"

      "              highp float depth = 1.0;                                                                                                                                 \n"      
      "              a           =  -depth / vertex_pos.z;                                                                                                              \n"
      "              s           = vertex_pos * a * 0.5;                                                                                                                \n"
      "              s.z         = 1.0;                                                                                                                                 \n"
      "              s           = s;                                                                                                                                   \n"  
      
      "              pt_eye      = highp vec3 (varTexcoord, 0.0);                                                                                                             \n"
      
//       "              intersect_square_cone_3step (pt_eye, s);                                                                                                         \n"               

"               highp float iz = max(abs(s.x), abs(s.y));                                                                                                                          \n"

"               highp float w  = 0.43;                                                                                                                                             \n"

"               highp vec4  t;                                                                                                                                                      \n"
"               pt_eye += 0.261004 * s;                                                                                                                                      \n"

//-------------------------------------------------------------
"               t=texture2D(HeightMap, pt_eye.xy);                                                                                                                                  \n"
"               pt_eye += s * w * (t.r*t.r - pt_eye.z) / ((iz/t.g) + 1.0);                                                                                                         \n"
//-------------------------------------------------------------
"               t=texture2D(HeightMap, pt_eye.xy);                                                                                                                                  \n"
"               pt_eye += s * w * (t.r*t.r - pt_eye.z) / ((iz/t.g) + 1.0);                                                                                                         \n"
//-------------------------------------------------------------
"               t=texture2D(HeightMap, pt_eye.xy);                                                                                                                                  \n"
"               pt_eye += s * w * (t.r*t.r - pt_eye.z) / ((iz/t.g) + 1.0);                                                                                                         \n"
//-------------------------------------------------------------

      //-----------------------------------------------------------------------------------------------------------------------------     
/*      
      " 		         vec4  shadowCoordinateWdivide    =  shadowTexcoord / shadowTexcoord.w;                                         \n" 
      " 		               shadowCoordinateWdivide.z +=  -0.2855;                                                                   \n" 
      " 		         float distanceFromLight          =  shadow2DProj(ShadowTexture, shadowTexcoord).r;                             \n" 
     
      " 		         float shadow                     =  1.0;                                                                       \n" 
      " 		         if (shadowTexcoord.w             >  0.0)                                                                       \n" 
      " 		      		  shadow = distanceFromLight  <  shadowCoordinateWdivide.z ? 0.4 : 1.0 ;                                \n"   
*/     
      //-----------------------------------------------------------------------------------------------------------------------------    
      "     highp float comp = (shadowTexcoord.z / shadowTexcoord.w) - 8.4e-005;                                                                           \n" 
      "     highp float depth_PowerVR = texture2DProj(ShadowTexture, shadowTexcoord).r;                                                         \n" 
      "     highp float shadowVal = comp <= depth_PowerVR ? 1.0 : 0.4;                                                                          \n" 
      //-----------------------------------------------------------------------------------------------------------------------------       
      "         highp vec4 c                 =  texture2D(Texture1, pt_eye.xy);                                                                 \n" 
      //------------------------------------------------------------------------------------   
      "         NormalTex              =  texture2D(NormalMap,  pt_eye.xy).xyz;                                                                 \n"                       
      "         NormalTex              = (NormalTex - 0.5);                                                                                     \n"        
      "         normal_2               =  normalize(NormalTex);                                                                                 \n"      
      "         NdotL2                 =  max(dot(normal_2, lightPosition_PASS.xyz), 0.0);                                                      \n"      
      "         highp float shiny            =  pow(NdotL2,60.0);                                                                               \n"      
      //-----------------------------------------------------------------------------------------------------------------------------
      "         highp float glAttenuation_L1;                                                                                                   \n"
      "         glAttenuation(glAttenuation_L1, dist);                                                                                          \n"
      //-----------------------------------------------------------------------------------------------------------------------------  
      "         gl_FragColor           = (c * NdotL2 + c * highp vec4(1.0, 1.0, 1.0, 1.0) * shiny * c) * shadowVal * glAttenuation_L1;          \n"
      
      
      //"////|TextureMapSpace|////   gl_FragColor           = vec4((varTexcoord.x+.5)/2.0, (varTexcoord.y +.5)/2.0, 0.0, 0.0);                  \n"
      
      "    }\n"                                                                                                                                   

//=============================================================================================================================
" highp float glAttenuation(inout highp float inOutAttenuation, in highp float distanceToLight)                                                     \n" 
"{                                                                                                                                              \n" 
 
      "         highp float attenuation = 1.0 / (constantAttenuation                                                                            \n"
      "                                      + linearAttenuation    * distanceToLight                                                           \n"
      "                                      + quadraticAttenuation * distanceToLight * distanceToLight);                                       \n" 
     
      "         inOutAttenuation = attenuation ;                                                                                                \n" 
      "         return inOutAttenuation;                                                                                                        \n"
"}                                                                                                                                              \n" 


//==============================================================================================================================   
/*
" highp float linearLight(inout highp float inOutAttenuation, in highp vec3 VertexPos)                                                              \n" 
"{                                                                                                                                              \n" 
 
      "         highp float attenuation = 1.0 / (1.0                                                                                            \n"
      "                                      + 0.385    * VertexPos                                                                             \n"
      "                                      + .063 * VertexPos * VertexPos);                                                                   \n" 
     
      "         inOutAttenuation = attenuation ;                                                                                                \n" 
      "         return inOutAttenuation;                                                                                                        \n"
"}                                                                                                                                              \n"   
*/                                                                                                                            
//==============================================================================================================================   
/*
" float  imdoingitwrong (inout float imDoingItWrongAttenuation, in vec3 vertexPosition)                                                                                  \n"
"{                                                                                                                                              \n"
   
      "         float r = 4.0;                                                                                                                  \n" 
      " 	    vec3 L  = normalize(light_POSITION_01.xyz )- vertexPosition;                                                                                        \n" 
      " 	    float distance = length(L);                                                                                                 \n" 
      " 	    float d = max(distance - r, 0.0);                                                                                           \n" 
      "	        L /= distance;                                                                                                                  \n"

      " 	    float denom = d/r + 1.0;                                                                                          \n" 
      " 	    float att = 1.0 / (denom*denom);                                                                                  \n" 
	     
      "	        att = (att - imDoingItWrongAttenuation) / (1.0 - imDoingItWrongAttenuation);                                      \n" 
      "	        imDoingItWrongAttenuation = max(att,  0.0);                                                                       \n" 
      "	        return imDoingItWrongAttenuation;                                                                                 \n" 

"}	                                                                                                                              \n"      

*/ 
//===========================================================================================================================


"void intersect_square_cone_3step (inout highp vec3 dp, in highp vec3 ds)                                                                   \n"
"{                                                                                                                              \n"

"   highp float iz = max(abs(ds.x),abs(ds.y));                                                                                        \n"

"   highp float w  = .43;                                                                                                             \n"
//"   float w  = constantAttenuation;                                                                                           \n"

"   highp vec4 t;                                                                                                                     \n"
//============================================================
//"   	float db = (0.991001) - ds.z;                                                                                                  \n"
//"   	db *= db;                                                                                                               \n"
//"  	    db = (1.581) - db*db;                                                                                               \n"
//"    	ds.xy *= db;                                                                                                            \n"
//============================================================
"   dp += 0.261004 * ds;                                                                                                        \n"
//"   dp += shininess * ds;                                                                                                     \n"       

//-------------------------------------------------------------
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                         \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.02
//_________________________________shininess            =  0.43
//============================================================  
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                         \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.46
//_________________________________shininess            =  0.2
//============================================================   
"   t=texture2D(HeightMap,dp.xy);                                                                                               \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                         \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.46
//_________________________________shininess            =  0.2
//============================================================  




"   return;                                                                                                                     \n"
"}                                                                                                                              \n"

//===========================================================================================================================
/*
"   void ray_intersect_cone(inout vec3 p, inout vec3 v)                                                                         \n"
"   {                                                                                                                           \n"
"   	float dist = length(v.xy);                                                                                              \n"
	
"   	for(int i=0; i < 4; i++)                                                                                                \n"
"   	{                                                                                                                       \n"
"   		vec4 tex = texture2D(HeightMap, p.xy);                                                                              \n"
"   		float height = clamp((tex.w - p.z), 0.0, 1.0);;                                                                     \n"

"   		float cone_ratio = tex.z*tex.z;                                                                                     \n"
		
		         //float stepDist = height * cone_ratio / (v.z*cone_ratio + dist);                                              \n"
"   		float stepDist = height * cone_ratio / (cone_ratio + dist);                                                         \n"
"   		p += v * stepDist;                                                                                                  \n"
		
		        //===========================================================
		        //float4 tex = tex2D(cone_map, p.xy);                                                                           \n"
		        //float height = max(0, tex.w - p.z);                                                                           \n"
		        //float stepDist = height * 0.2;                                                                                \n"
		        //p += v * stepDist;                                                                                            \n"
		        //--------------------------------------------------------
		        //float stepDist = height * cone_ratio / (cone_ratio + 0.1);                                                    \n"
		        //--------------------------------------------------------
		        //p += v * height * cone_ratio / (v.z*cone_ratio + dist);                                                       \n"
		        //===========================================================
"   	}                                                                                                                       \n"
"     return;                                                                                                                   \n"

"    }                                                                                                                          \n"
*/
//===========================================================================================================================
/*"   void setVIEW_ray_ps(in vec3 texCoordinates, out vec3 rayPos, out vec3 rayVec)                                             \n"
//"   {                                                                                                                         \n"
"   	rayPos = float3(IN.uv0, 0.0);                                                                                           \n"
	
"   	rayVec = normalize(IN.eyeVec);                                                                                          \n"
"   	rayVec.z = abs(rayVec.z);                                                                                               \n"


//"   	if (DEPTH_BIAS) //Depth bias used by Fabio Policarpo                                                                                              \n"
//"   	{                                                                                                                       \n"
//"   		float db = 1.0 - rayVec.z;                                                                                          \n"
//"   		db *= db;                                                                                                           \n"
//"   		db = 1.0 - db*db;                                                                                                   \n"
//"   		rayVec.xy *= db;                                                                                                    \n"
//"   	}                                                                                                                       \n"
	
"   	rayVec.xy *= depth;                                                                                                     \n"
"   }                                                                                                                           \n"
*/
//===========================================================================================================================
/*
vec4 bump_ps(vec2 uv0, vec3 eyeVec, vec3 lightVec)
{
	if (BORDER_CLAMP)
	{
		if (uv0.x < 0.0) discard;
		if (uv0.x > tile) discard;
		if (uv0.y < 0.0) discard;
		if (uv0.y > tile) discard;
	}

	// View and light vectors
	float3 v = normalize(eyeVec);
	float3 l1 = normalize(lightVec);
	
	// Diffuse texture color
	float3 color = tex2D(color_map, uv0).xyz;

	// Bump map
	float3 n = tex2D(cone_map, uv0);
	n.xy = n.xy * 2.0 - 1.0;
	n.y = -n.y;
	n.z = sqrt(1.0 - dot(n.xy, n.xy));
	
	return phongShading(n, l1, -v, color);
}
*/
//===========================================================================================================================



;



      //---------------------------------------------------------------------                                                                         
      steepPointy_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(steepPointy_SHADER_FRAGMENT, 1, &fragmentSource_steepPointy, NULL);                                                                          
      glCompileShader(steepPointy_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(steepPointy_SHADER, steepPointy_SHADER_VERTEX);                                                                                              
      glAttachShader(steepPointy_SHADER, steepPointy_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(steepPointy_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(steepPointy_SHADER, 1, "normal");       
      glBindAttribLocation(steepPointy_SHADER, 2, "tangent");  
      glBindAttribLocation(steepPointy_SHADER, 3, "texture");                                                                                              
      //------------------------------------------------                                                                                              
      glLinkProgram(steepPointy_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(steepPointy_SHADER, steepPointy_SHADER_VERTEX);                                                                                              
      glDetachShader(steepPointy_SHADER, steepPointy_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(steepPointy_SHADER_VERTEX);                                                                                                            
      glDeleteShader(steepPointy_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------------------------                
      UNIFORM_MODELVIEWPROJ_steepPointy                   = glGetUniformLocation(steepPointy_SHADER,   "mvpMatrix");
      UNIFORM_MODELVIEW_steepPointy                       = glGetUniformLocation(steepPointy_SHADER,   "mvMatrix");        
      //-------------------------------      
      UNIFORM_viewMatrix_steepPointy                      = glGetUniformLocation(steepPointy_SHADER,   "viewMatrix");              
      //-------------------------------
      UNIFORM_SHADOW_PROJ_steepPointy                     = glGetUniformLocation(steepPointy_SHADER,   "projectionShadow");                                                    
      UNIFORM_modelViewShadow_steepPointy                 = glGetUniformLocation(steepPointy_SHADER,   "modelViewShadow");                                                    
      //-------------------------------      
      UNIFORM_LIGHT_MATRIX_steepPointy                    = glGetUniformLocation(steepPointy_SHADER,   "lightMatrix");                                            
      UNIFORM_textureMatrix_steepPointy                   = glGetUniformLocation(steepPointy_SHADER,   "textureMatrix");       
      UNIFORM_INVERSEMATRIX_steepPointy                   = glGetUniformLocation(steepPointy_SHADER,   "inverseMatrix");   
      UNIFORM_offset_steepPointy                          = glGetUniformLocation(steepPointy_SHADER,   "offset");      
      //-------------------------------------
      UNIFORM_LIGHT_POSITION_01_steepPointy               = glGetUniformLocation(steepPointy_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_steepPointy                       = glGetUniformLocation(steepPointy_SHADER,   "shininess");                                              
      //-------------------------------------
      UNIFORM_CONSTANT_ATTENUATION_steepPointy            = glGetUniformLocation(steepPointy_SHADER,   "constantAttenuation");      
      UNIFORM_LINEAR_ATTENUATION_steepPointy              = glGetUniformLocation(steepPointy_SHADER,   "linearAttenuation");      
      UNIFORM_QUADRATIC_ATTENUATION_steepPointy           = glGetUniformLocation(steepPointy_SHADER,   "quadraticAttenuation");
      //-------------------------------------
      UNIFORM_zDirBias_steepPointy                        = glGetUniformLocation(steepPointy_SHADER,   "zDirBias");      
      //-------------------------------------
      UNIFORM_TEXTURE_SHADOW_steepPointy                  = glGetUniformLocation(steepPointy_SHADER,   "ShadowTexture");        
      UNIFORM_TEXTURE_HEIGHT_steepPointy                  = glGetUniformLocation(steepPointy_SHADER,   "HeightMap");                                                      
      UNIFORM_TEXTURE_DOT3_steepPointy                    = glGetUniformLocation(steepPointy_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_steepPointy                         = glGetUniformLocation(steepPointy_SHADER,   "Texture1");                                               
      //---------------------------------------------------------------------------------------------------------------------------------     
