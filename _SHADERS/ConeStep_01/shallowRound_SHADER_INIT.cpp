     #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      shallowRound_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_shallowRound =                                                                                                        

      "    #define highp                                                                                                                                                \n"                           
 
                     
        "    uniform       mat4  mvpMatrix;                                                                                                                             \n"                           
        "    uniform       mat4  mvMatrix;                                                                                                                              \n"        
        //-----------------------------------------
        "    uniform       mat4  viewMatrix;                                                                                                                            \n"                   
        //-----------------------------------------
        "    uniform       mat4  projectionShadow;                                                                                                                      \n"        
        "    uniform       mat4  modelViewShadow;                                                                                                                       \n"        
      
                                                            
        "    uniform       mat4  undoMatrix;                                                                                                                            \n"     
        "    uniform       mat4  textureMatrix;                                                                                                                         \n"         
        //-----------------------------------------       
/*    
        "    uniform highp float shininess;                                                                                                                             \n"                       
        //--------------------------------------------
        "    uniform highp float quadraticAttenuation;                                                                                                                  \n"                       
        "    uniform highp float linearAttenuation;                                                                                                                     \n"  
        "    uniform highp float constantAttenuation;                                                                                                                   \n" 
*/     //--------------------------------------------
        "    attribute     vec4  position;                                                                                                                              \n"                           
        "    attribute     vec3  normal;                                                                                                                                \n"         
        "    attribute     vec3  tangent;                                                                                                                               \n"             
   
        "    attribute     vec2  texture;                                                                                                                               \n"                           
        "    varying highp vec2  varTexcoord;                                                                                                                           \n"                           
        //--------------------------------------------
        "    uniform       mat4  lightMatrix;                                                                                                                           \n"        
        "    uniform highp vec4  light_POSITION_01;                                                                                                                     \n"       
        "    varying highp vec4  lightPosition_PASS;                                                                                                                    \n"         
        //--------------------------------------------
        "    varying highp vec4  shadowTexcoord;                                                                                                                        \n"       
        //--------------------------------------------      
     
       
        "    varying highp vec3  aux;                                                                                                                                   \n"       
        "    varying highp float dist;                                                                                                                                  \n" 
        "            highp vec4  ecPos;                                                                                                                                 \n" 
       
        //-----------------------------------------------------------------------------------------------------------------
        "    varying highp vec3  vertex_pos;                                                                                                                            \n" 
        //-----------------------------------------------------------------------------------------------------------------      
        "    const mat4  ScaleMatrix = mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);                                            \n"  
 
        //========================================================================================================================== 
        "    void main()                                                                                                                                                \n"                           
        "    {                                                                                                                                                          \n"                           
   
        "               highp vec3 eyeSpaceVert     =  highp vec3(mvMatrix * position);                                                                             \n"
                        //----------------
        "               highp vec3 eyeSpaceNormal   =  highp vec3(mvMatrix * vec4(normal, 0.0));                                                                    \n"  
        "               highp vec3 eyeSpaceTangent  =  highp vec3(mvMatrix * vec4(tangent, 0.0));                                                                   \n"  
        "               highp vec3 eyeSpaceBinormal =   cross(eyeSpaceNormal, eyeSpaceTangent);                                                                         \n"  
                        //---------------------------------------------------------------------------------------------------------    
        "               vertex_pos            =  highp vec3 ( dot (eyeSpaceTangent,  eyeSpaceVert),                                                                     \n" 
        "                                                     dot (eyeSpaceBinormal, eyeSpaceVert),                                                                     \n" 
        "                                                     dot (eyeSpaceNormal,   eyeSpaceVert));                                                                    \n" 
                        //---------------------------------------------------------------------------------------------------------     
        "               shadowTexcoord        =   ScaleMatrix * projectionShadow * modelViewShadow * viewMatrix * mvMatrix * position;                                  \n" 
//      "               shadowTexcoord        =   shadowTexcoord / shadowTexcoord.w;                                                                                    \n"      
                       //---------------------------------------------------------------------------------------------------------
        "               lightPosition_PASS    =   normalize(lightMatrix * light_POSITION_01);                                                                           \n" 
                        //-------------------------------------------------------------------------
        "               ecPos                 =   mvMatrix * position;                                                                                                  \n" //this portion comes from --> Lighthouse3d.com
        "               aux                   =   highp vec3(ecPos - lightPosition_PASS );                                                                                    \n" //this portion comes from --> Lighthouse3d.com 
        "               dist                  =   length(aux);                                                                                                          \n" //this portion comes from --> Lighthouse3d.com 
                        //--------------------------------------------------------  
        "               varTexcoord           =   texture;                                                                                                              \n"                           
 
 
 "               gl_Position           =   mvpMatrix * position;                                                                                                        \n"                           

        "    }\n";                                                                                                                             
      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################      
//#################################################################################################################################        
   
   
      //---------------------------------------------------------------------                                                                   
      shallowRound_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(shallowRound_SHADER_VERTEX, 1, &vertexSource_shallowRound, NULL);                                                                        
      glCompileShader(shallowRound_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
        const GLchar *fragmentSource_shallowRound =                                                                                                            

        " #ifdef GL_ES                                                                                                                                                  \n"                       
        " #else                                                                                                                                                         \n"                       
        " #define highp                                                                                                                                                 \n"                       
        " #define lowp                                                                                                                                                 \n"                       
        " #endif                                                                                                                                                        \n"                       

        //--------------------------------------------
        "    uniform highp sampler2D   Texture1;                                                                                                                              \n"                       
        //--------------------------------------------
        "    uniform highp sampler2D   NormalMap;                                                                                                                             \n"                       
        "            highp float NdotL2;                                                                                                                                \n"                       
        "            highp vec3  normal_2;                                                                                                                              \n"                       
        "            highp vec3  NormalTex;                                                                                                                             \n"                       
        //--------------------------------------------
        "    varying highp vec2  varTexcoord;                                                                                                                           \n"                       
        //--------------------------------------------
       "    uniform highp vec4  light_POSITION_01;                                                                                                                    \n"    
        "    varying highp vec4  lightPosition_PASS;                                                                                                                    \n"      
//--------------------------------------------
        "    uniform highp sampler2D   HeightMap;                                                                                                                             \n"        
        //--------------------------------------------
        "    uniform highp sampler2D   ShadowTexture;                                                                                                                         \n"     
        "    varying highp vec4  shadowTexcoord;                                                                                                                        \n"       
         //--------------------------------------------
        "    uniform highp float shininess;                                                                                                                             \n"                       
                     
        //--------------------------------------------  
        "    uniform highp float constantAttenuation;                                                                                                                   \n" 
        "    uniform highp float linearAttenuation;                                                                                                                     \n"  
        "    uniform highp float quadraticAttenuation;                                                                                                                  \n"                       
        //--------------------------------------------
        "    varying highp vec3  aux;                                                                                                                                   \n"       
        "    varying highp float dist;                                                                                                                                \n" 
        //--------------------------------------------
        "    varying highp vec3 vertex_pos;                                                                                                                             \n" 
        //--------------------------------------------

        //=============================================================================================================================     
        "    highp float glAttenuation(inout highp float inOutAttenuation, in highp float distanceToLight);                                                                                 \n"      
        //=============================================================================================================================        
        "    void intersect_square_cone_3step (inout highp vec3 dp, in highp vec3 ds);                                                                                  \n" 
//      "    void ray_intersect_cone(inout vec3 p, inout vec3 v);                                                                                                       \n" 
//     "    void setup_ray_ps(in vec2 texCoordinates, out vec3 rayPos, out vec3 rayVec);                                                                                \n"       
        //=============================================================================================================================     
/*
        //----------------------------------------------------------------------------------------
        "        mat3 cotangent_frame( vec3 N, vec3 p, vec2 uv )                                                                                                        \n" 
        "        {                                                                                                                                                      \n" 
        "            // get edge vectors of the pixel triangle                                                                                                          \n" 
        "            vec3 dp1 = dFdx( p );                                                                                                                              \n" 
        "            vec3 dp2 = dFdy( p );                                                                                                                              \n" 
        "            vec2 duv1 = dFdx( uv );                                                                                                                            \n" 
        "            vec2 duv2 = dFdy( uv );                                                                                                                            \n" 
 
        "            // solve the linear system                                                                                                                         \n" 
        "            vec3 dp2perp = cross( dp2, N );                                                                                                                    \n" 
        "            vec3 dp1perp = cross( N, dp1 );                                                                                                                    \n" 
        "            vec3 T = dp2perp * duv1.x + dp1perp * duv2.x;                                                                                                      \n" 
        "            vec3 B = dp2perp * duv1.y + dp1perp * duv2.y;                                                                                                      \n" 
 
        "            // construct a scale-invariant frame                                                                                                               \n" 
        "            float invmax = inversesqrt( max( dot(T,T), dot(B,B) ) );                                                                                           \n" 
        "            return mat3( T * invmax, B * invmax, N );                                                                                                          \n"                                                                     
        "        }                                                                                                                                                      \n" 
      //----------------------------------------------------------------------------------------
*/
        "     void main()                                                                                                                                               \n"                       
        "     {                                                                                                                                                         \n"                       

        "               highp vec3 s;                                                                                                                                    \n"
        "               highp vec3 pt_eye;                                                                                                                               \n"
        "               highp float a;                                                                                                                                   \n"

        "               highp float depth = .15;                                                                                                                         \n"      
        "               a           = -depth / vertex_pos.z;                                                                                                             \n"
        "               s           = vertex_pos * a;                                                                                                                    \n"
        "               s.z         = 1.0;                                                                                                                               \n"
        "               s           = s;                                                                                                                                 \n"  
        
        "               pt_eye      = vec3 (varTexcoord, 0.0);                                                                                                           \n"
      
//       "              intersect_square_cone_3step (pt_eye, s);                                                                                                         \n"               

        "               highp float iz = max(abs(s.x), abs(s.y));                                                                                                                          \n"

        "               highp float w  = 0.28;                                                                                                                                             \n"

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



/*                      //---------------------------------------------------------
        " 		     if (pt_eye.x < 0.0) discard;                                                                                                               \n" 
        " 		     if (pt_eye.x > 1.0) discard;                                                                                                               \n" 
        " 		     if (pt_eye.y < 0.0) discard;                                                                                                               \n" 
        " 		     if (pt_eye.y > 1.0) discard;                                                                                                               \n" 
  */       //-----------------------------------------------------------------------------------------------------------------------------     
/*              
        " 		         vec4  shadowCoordinateWdivide    =  shadowTexcoord / shadowTexcoord.w;                                                                 \n" 
        " 		               shadowCoordinateWdivide.z +=  -0.2855;                                                                                           \n" 
        " 		         float distanceFromLight          =  shadow2DProj(ShadowTexture, shadowTexcoord).r;                                                     \n" 
     
        " 		         float shadow                     =  1.0;                                                                                               \n" 
        " 		         if (shadowTexcoord.w             >  0.0)                                                                                               \n" 
        " 		      		  shadow = distanceFromLight  <  shadowCoordinateWdivide.z ? 0.4 : 1.0 ;                                                        \n"   
*/   //-----------------------------------------------------------------------------------------------------------------------------
        "     highp float comp = (shadowTexcoord.z / shadowTexcoord.w) - 8.4e-005;                                                                                      \n" 
        "     highp float depth_PowerVR = texture2DProj(ShadowTexture, shadowTexcoord).r;                                                                               \n" 
        "     lowp float shadowVal = comp <= depth_PowerVR ? 1.0 : 0.4;                                                                                                \n" 
      //-----------------------------------------------------------------------------------------------------------------------------       
        "         highp vec4 c                  =  texture2D(Texture1, pt_eye.xy);                                                                                      \n" 
        //------------------------------------------------------------------------------------   
        "         NormalTex                     =  texture2D(NormalMap,  pt_eye.xy).xyz;                                                                                \n"                       
        "         NormalTex                     = (NormalTex - 0.5);                                                                                                    \n"        
        "         normal_2                      =  normalize(NormalTex);                                                                                                \n"      
        "         NdotL2                        =  max(dot(normal_2, lightPosition_PASS.xyz), 0.0);                                                                     \n"      
        "         highp float shiny             =  pow(NdotL2,60.0);                                                                                                    \n"      
        //-----------------------------------------------------------------------------------------------------------------------------
        "         highp float glAttenuation_L1;                                                                                                                       \n"
        "         glAttenuation(glAttenuation_L1, dist);                                                                                                               \n"
        //-----------------------------------------------------------------------------------------------------------------------------  
     
        "         gl_FragColor           = (c * NdotL2 + c * highp vec4(1.0, 1.0, 1.0, 1.0) * shiny * c) * shadowVal * glAttenuation_L1;                                                  \n"   
         
      
        
                 //"////|TextureMapSpace|////   gl_FragColor           = vec4((varTexcoord.x+.5)/2.0, (varTexcoord.y +.5)/2.0, 0.0, 0.0);                               \n"
      
        "    }\n"                                                                                                                                   


//=====================================================================================================================================



" highp float glAttenuation(inout highp float inOutAttenuation, in highp float distanceToLight)                                                                                           \n" 
"{                                                                                                                                                                      \n" 
 
      "         highp float attenuation = 1.0 / (constantAttenuation                                                                                                          \n"
      "                                      + linearAttenuation    * distanceToLight                                                                                   \n"
      "                                      + quadraticAttenuation * distanceToLight * distanceToLight);                                                               \n" 
     
      "         inOutAttenuation = attenuation ;                                                                                                                        \n" 
      "         return inOutAttenuation;                                                                                                                                \n"
"}                                                                                                                                                                      \n" 


//=====================================================================================================================================


"void intersect_square_cone_3step (inout highp vec3 dp, in highp vec3 ds)                                                                                               \n"
"{                                                                                                                                                                      \n"

"   highp float iz = max(abs(ds.x),abs(ds.y));                                                                                                                          \n"

"   highp float w  = (.28);                                                                                                                                             \n"

"   highp vec4  t;                                                                                                                                                      \n"
//============================================================
//"   	float db = (0.991001) - ds.z;                                                                                                                                   \n"
//"   	db *= db;                                                                                                                                                       \n"
//"  	    db = (1.581) - db*db;                                                                                                                                       \n"
//"    	ds.xy *= db;                                                                                                                                                    \n"
//============================================================
"       dp += (0.261004) * ds;                                                                                                                                          \n"
//"     dp += shininess * ds;                                                                                                                                           \n"

//-------------------------------------------------------------
"   t=texture2D(HeightMap, dp.xy);                                                                                                                                       \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                                                                 \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.02
//_________________________________shininess            =  0.43
//============================================================  
"   t=texture2D(HeightMap,dp.xy);                                                                                                                                       \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                                                                 \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.46
//_________________________________shininess            =  0.2
//============================================================   
"   t=texture2D(HeightMap,dp.xy);                                                                                                                                       \n"
"   dp += ds * w * (t.r*t.r - dp.z) / (iz/(t.g) + 1.0);                                                                                                                 \n"
//--------------------------------
//_________________________________constantAttenuation  =  1.46
//_________________________________shininess            =  0.2
//============================================================  




"   return;                                                                                                                                                             \n"
"}                                                                                                                                                                      \n"



;



      //---------------------------------------------------------------------                                                                         
      shallowRound_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(shallowRound_SHADER_FRAGMENT, 1, &fragmentSource_shallowRound, NULL);                                                                          
      glCompileShader(shallowRound_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(shallowRound_SHADER, shallowRound_SHADER_VERTEX);                                                                                              
      glAttachShader(shallowRound_SHADER, shallowRound_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(shallowRound_SHADER, 0, "position");                                                                                            
      glBindAttribLocation(shallowRound_SHADER, 1, "normal");       
      glBindAttribLocation(shallowRound_SHADER, 2, "tangent");  
      glBindAttribLocation(shallowRound_SHADER, 3, "texture");                                                                                             
      //------------------------------------------------                                                                                              
      glLinkProgram(shallowRound_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(shallowRound_SHADER, shallowRound_SHADER_VERTEX);                                                                                              
      glDetachShader(shallowRound_SHADER, shallowRound_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(shallowRound_SHADER_VERTEX);                                                                                                            
      glDeleteShader(shallowRound_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_shallowRound                   = glGetUniformLocation(shallowRound_SHADER,   "mvpMatrix"); 
      UNIFORM_MODELVIEW_shallowRound                       = glGetUniformLocation(shallowRound_SHADER,   "mvMatrix");        
      //-------------------------------      
      UNIFORM_viewMatrix_shallowRound                      = glGetUniformLocation(shallowRound_SHADER,   "viewMatrix");              
      //-------------------------------
      UNIFORM_SHADOW_PROJ_shallowRound                     = glGetUniformLocation(shallowRound_SHADER,   "projectionShadow");                                                  
      UNIFORM_modelViewShadow_shallowRound                 = glGetUniformLocation(shallowRound_SHADER,   "modelViewShadow");            
      //-------------------------------
      UNIFORM_LIGHT_MATRIX_shallowRound                    = glGetUniformLocation(shallowRound_SHADER,   "lightMatrix");                                            
      UNIFORM_textureMatrix_shallowRound                   = glGetUniformLocation(shallowRound_SHADER,   "textureMatrix");       
      UNIFORM_offset_shallowRound                          = glGetUniformLocation(shallowRound_SHADER,   "offset");      
      //-------------------------------------
      UNIFORM_CONSTANT_ATTENUATION_shallowRound            = glGetUniformLocation(shallowRound_SHADER,   "constantAttenuation");       
      UNIFORM_LINEAR_ATTENUATION_shallowRound              = glGetUniformLocation(shallowRound_SHADER,   "linearAttenuation");      
      UNIFORM_QUADRATIC_ATTENUATION_shallowRound           = glGetUniformLocation(shallowRound_SHADER,   "quadraticAttenuation");
      //-------------------------------------
      UNIFORM_LIGHT_POSITION_01_shallowRound               = glGetUniformLocation(shallowRound_SHADER,   "light_POSITION_01");                                      
      UNIFORM_SHININESS_shallowRound                       = glGetUniformLocation(shallowRound_SHADER,   "shininess");                                              
      //-------------------------------------
      UNIFORM_TEXTURE_SHADOW_shallowRound                  = glGetUniformLocation(shallowRound_SHADER,   "ShadowTexture");        
      UNIFORM_TEXTURE_HEIGHT_shallowRound                  = glGetUniformLocation(shallowRound_SHADER,   "HeightMap");                                                      
      UNIFORM_TEXTURE_DOT3_shallowRound                    = glGetUniformLocation(shallowRound_SHADER,   "NormalMap");                                              
      UNIFORM_TEXTURE_shallowRound                         = glGetUniformLocation(shallowRound_SHADER,   "Texture1");                    
