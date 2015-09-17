    #ifdef __APPLE__                                                                                                                          
      #import <OpenGLES/ES2/gl.h>                                                                                                               
      #import <OpenGLES/ES2/glext.h>                                                                                                            
      #endif                                                                                                                                    
      //===============================================================================================                                         
      rubber_SHADER = glCreateProgram();                                                                                                         
      //---------------------------------------------------------------------                                                                   
      const GLchar *vertexSource_rubber =                                                                                                        

      "    #define highp                                                                                                                         \n"        

      "    uniform highp vec4   light_POSITION_01;                                                                                               \n"        
      "    uniform       mat4   mvpMatrix;                                                                                                       \n"      
      "    uniform       mat4   mvMatrix;                                                                                                        \n"  
           //-----
      "    uniform       mat4   viewMatrix;                                                                                                      \n"                   
           //-----
      "    uniform       mat4   projectionShadow;                                                                                                \n"        
      "    uniform       mat4   modelViewShadow;                                                                                                 \n"        
           //-----   
      "    uniform       mat4   lightMatrix;                                                                                                     \n"     
      "    uniform       mat4   textureMatrix;                                                                                                   \n"  
      "    attribute     vec4   position;                                                                                                        \n"      
      //--------------------------------------------
      "    attribute     vec3   normal;                                                                                                          \n"      
      "    varying highp vec3   normal_PASS;                                                                                                     \n"   
      //--------------------------------------------
      "    attribute     vec2   texture;                                                                                                         \n"       

      "    varying highp vec4   lightPosition_PASS;                                                                                              \n" 
      //--------------------------------------------      
      "    varying highp vec4   shadowTexcoord;                                                                                                  \n"
      "            const mat4   ScaleMatrix = mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);              \n"
      //-------------------------------------------- 
      "    varying highp vec2  varTexcoord;                                                                                                      \n"
      
      "    varying highp vec4   diffuse;                                                                                                         \n"
      "    varying highp vec4   ambientGlobal;                                                                                                   \n"
      "    varying highp float  dist;                                                                                                            \n"
      "            highp vec4   ecPos;                                                                                                           \n"
      "            highp vec3   aux;                                                                                                             \n"
      //=========================================================================================================================================
      "    void main()                                                                                                                           \n" 
      "    {                                                                                                                                     \n"
                   //---------------------------------------------------------------------------------------------------------
//      "            ecPos                 =  mvpMatrix * position;                                                                                \n"
//      "            aux                   =  vec3(light_POSITION_01 - ecPos);                                                                     \n"
//      "            dist                  =  length(aux);                                                                                         \n"

//      "            diffuse               =  highp  vec4(  -1.925, 2.925 , 2.925, 1.0);                                                           \n"
//      "            ambientGlobal         =  highp  vec4(-1.75, -1.75, 0.0, 1.0);                                                                 \n"                                       
                   //---------------------------------------------------------------------------------------------------------     
//      "            normal_PASS           =  normalize(mvMatrix * vec4(normal, 1.0)).xyz;                                                                       \n"
//      "            shadowTexcoord        =  ScaleMatrix * projectionShadow * modelViewShadow * viewMatrix * mvMatrix * position;                 \n" 
//      "            shadowTexcoord        =  shadowTexcoord / shadowTexcoord.w;                                                                   \n"      
                   //---------------------------------------------------------------------------------------------------------
      "            lightPosition_PASS    =  normalize(lightMatrix * light_POSITION_01);                                                          \n"        
      "            varTexcoord           =  texture;                                                                                             \n"          
      "            gl_Position           =  mvpMatrix * position;                                                                                \n"           

      "    }\n";                                                                                                                             
      
      
      //---------------------------------------------------------------------                                                                   
      rubber_SHADER_VERTEX = glCreateShader(GL_VERTEX_SHADER);                                                                                   
      glShaderSource(rubber_SHADER_VERTEX, 1, &vertexSource_rubber, NULL);                                                                        
      glCompileShader(rubber_SHADER_VERTEX);                                                                                                     
      //---------------------------------------------------------------------                                                                   
      const GLchar *fragmentSource_rubber =                                                                                                            

      " #ifdef GL_ES                                                                                                                             \n"                       
      " #else                                                                                                                                    \n"                       
      " #define highp                                                                                                                            \n"                       
      " #endif                                                                                                                                   \n"   
    
      "    uniform sampler2D   Texture1;                                                                                                         \n"                       
      "    uniform sampler2D   NormalMap;                                                                                                        \n"                       
      //--------------------------------------------
      "    uniform highp float shininess;                                                                                                        \n"                       
      "    uniform highp float attenuation;                                                                                                      \n"                       

      "    varying highp vec4  lightPosition_PASS;                                                                                               \n"                       
      "    varying highp vec2  varTexcoord;                                                                                                      \n"                       

      "            highp float NdotL1;                                                                                                           \n"                       
      "            highp vec3  normal_1;                                                                                                           \n"                       
      "            highp vec3  NormalTex;                                                                                                        \n"                       
      
      "    uniform highp vec4  light_POSITION_01;                                                                                               \n"       
      "    varying highp vec3  normal_PASS;                                                                                                      \n"   

      "    varying highp vec4  diffuse;                                                                                                          \n"
      "    varying highp vec4  ambientGlobal;                                                                                                    \n"
   
      "    varying highp float dist;                                                                                                             \n"

      "            highp float att;                                                                                                              \n"
      "            highp vec4  color;                                                                                                            \n"
      //=========================================================================================================================================
      "     void main()                                                                                                                          \n"                       
      "     {                                                                                                                                    \n"                       
   
      //-----------------------------------------------------------------------------------------------------------------------------     
      "         NormalTex                 =  texture2D(NormalMap,  varTexcoord).xyz;                                                             \n"                       
      "         NormalTex                 = (NormalTex - 0.5);                                                                                   \n"                       
      "         normal_1                    =  normalize(NormalTex);                                                                             \n"                       
      "         NdotL1                    =  max(dot(normal_1, lightPosition_PASS.xyz), 0.0);                                                    \n"                       

//      "         color                     =  ambientGlobal + (0.72 * diffuse);                                                                 \n"
    
//      "         color                    +=  vec4(1.0, 1.0, 1.0, 1.0) * pow(NdotL1, shininess) * 0.6;                                          \n"    
      
      "         gl_FragColor              =  vec4(1.0, 1.0, 1.0, 1.0) * NdotL1 * vec4(1.0, 1.0, shininess, 1.0);                                                      \n"                       

      "    }\n";                                                                                                                                   

      //---------------------------------------------------------------------fdgdf                                                                         
      rubber_SHADER_FRAGMENT = glCreateShader(GL_FRAGMENT_SHADER);                                                                                     
      glShaderSource(rubber_SHADER_FRAGMENT, 1, &fragmentSource_rubber, NULL);                                                                          
      glCompileShader(rubber_SHADER_FRAGMENT);                                                                                                         
      //------------------------------------------------                                                                                              
      glAttachShader(rubber_SHADER, rubber_SHADER_VERTEX);                                                                                              
      glAttachShader(rubber_SHADER, rubber_SHADER_FRAGMENT);                                                                                            
      //------------------------------------------------                                                                                              
      glBindAttribLocation(rubber_SHADER,    0, "position");                                                                                            
      glBindAttribLocation(rubber_SHADER,    1, "normal");       
      glBindAttribLocation(rubber_SHADER,    2, "texture");                                                                                           
      //------------------------------------------------                                                                                              
      glLinkProgram(rubber_SHADER);                                                                                                                    
      //------------------------------------------------                                                                                              
      #ifdef __APPLE__                                                                                                                                
      glDetachShader(rubber_SHADER, rubber_SHADER_VERTEX);                                                                                              
      glDetachShader(rubber_SHADER, rubber_SHADER_FRAGMENT);                                                                                            
      #endif                                                                                                                                          
      //------------------------------------------------                                                                                              
      glDeleteShader(rubber_SHADER_VERTEX);                                                                                                            
      glDeleteShader(rubber_SHADER_FRAGMENT);                                                                                                          
      //------------------------------------------------------------------------------------------------------------//___LOAD_UNIFORMS                
      UNIFORM_MODELVIEWPROJ_rubber                   = glGetUniformLocation(rubber_SHADER,      "mvpMatrix"); 
      UNIFORM_MODELVIEW_rubber                       = glGetUniformLocation(rubber_SHADER,      "mvMatrix");       
      //-------------------------------      
      UNIFORM_viewMatrix_rubber                      = glGetUniformLocation(rubber_SHADER,      "viewMatrix");              
      //-------------------------------
      UNIFORM_SHADOW_PROJ_rubber                     = glGetUniformLocation(rubber_SHADER,      "projectionShadow");                                                  
      UNIFORM_modelViewShadow_rubber                 = glGetUniformLocation(rubber_SHADER,      "modelViewShadow");            
      //-------------------------------                                              
      UNIFORM_LIGHT_MATRIX_rubber                    = glGetUniformLocation(rubber_SHADER,      "lightMatrix");                                            
      UNIFORM_textureMatrix_rubber                   = glGetUniformLocation(rubber_SHADER,      "textureMatrix"); 
      //-------------------------------  
      UNIFORM_SHADOW_PROJ_rubber                     = glGetUniformLocation(rubber_SHADER,      "projectionShadow");                                                  
      UNIFORM_modelViewShadow_rubber                 = glGetUniformLocation(rubber_SHADER,      "modelViewShadow");            
      //-------------------------------  
      UNIFORM_LIGHT_POSITION_01_rubber               = glGetUniformLocation(rubber_SHADER,      "light_POSITION_01");                                      
      UNIFORM_SHININESS_rubber                       = glGetUniformLocation(rubber_SHADER,      "shininess");                                              
     
      UNIFORM_TEXTURE_DOT3_rubber                    = glGetUniformLocation(rubber_SHADER,      "NormalMap");                                              
      UNIFORM_TEXTURE_rubber                         = glGetUniformLocation(rubber_SHADER,      "Texture1");                                   
