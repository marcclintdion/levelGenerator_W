    hardShinyBumpPlastic_SHADER = glCreateProgram();                                                                                     
        //----------------------------------------------------                                                                  
    const GLchar *vertexSource_hardShinyBumpPlastic =                                                                                    

      " #define highp                                                                                                                         \n" 
      
      
      "    attribute      vec4 position;                                                                                                      \n" 
      "    attribute      vec2 textureCoords;                                                                                                 \n" 
      "    //-------------------------------------------------                                                                                \n"     
      "    uniform  highp vec4  light_POSITION_01;                                                                                            \n" 
      "    uniform        mat4  mvMatrix;                                                                                                     \n" 
      "    uniform        mat4  mvpMatrix;                                                                                                    \n" 
           //-----
      "    uniform        mat4  viewMatrix;                                                                                                   \n"                   
           //-----
    "      uniform        mat4  projectionShadow;                                                                                             \n"        
    "      uniform        mat4  modelViewShadow;                                                                                              \n"        
           //-----
    "      uniform        mat4  LightMatrix;                                                                                                  \n" 
    "      uniform        mat4  TextureMatrix;                                                                                                \n" 
    //-------------------------------------------------                                                                
    "      varying highp  vec4  lightPosition_PASS;                                                                                           \n" 
    "      varying highp  vec2  varTexcoord;                                                                                                  \n" 
    //--------------------------------------------
    "      varying highp  vec4  shadowTexcoord;                                                                                               \n"       
    //--------------------------------------------
    "      const          mat4  ScaleMatrix = mat4(0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.0, 0.0, 0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 1.0);           \n"  

    //==================================================================================================================================
    
    " void main()                                                                                                                             \n" 
    " {                                                                                                                                       \n" 
                 //-------------------------------------------------------------------------------    
    "            shadowTexcoord   =   ScaleMatrix * projectionShadow * modelViewShadow * viewMatrix * mvMatrix * position;                                                         \n" 
    "            shadowTexcoord   =   shadowTexcoord / shadowTexcoord.w;                                                                      \n"      
                 //-------------------------------------------------------------------------------

    "            varTexcoord             = textureCoords;                                                                                     \n" 
    "            lightPosition_PASS      = normalize(LightMatrix * light_POSITION_01);                                                        \n" 
    
    "            gl_Position             = mvpMatrix * position;                                                                              \n" 
    
    " } \n";   
    
    //===================================================================================================================================                 

    const GLchar *fragmentSource_hardShinyBumpPlastic =                                                                                  

    "#ifdef GL_ES                                                                                                                           \n" 
    "#else                                                                                                                                  \n" 
    "#define highp                                                                                                                          \n" 
    "#endif                                                                                                                                 \n" 
    //-----------------------------------------------------------------------------------------------------------------------------------
    "     uniform sampler2D    NormalMap;                                                                                                   \n" 
    "             highp  vec3  NormalTex;                                                                                                   \n" 
    "             highp float  NdotL1;                                                                                                      \n" 
    //--------------------------------------------
    "    uniform sampler2D   ShadowTexture;                                                                                                 \n"   
    "    varying highp vec4  shadowTexcoord;                                                                                                \n"       
    //--------------------------------------------
    "     uniform sampler2D    Texture1;                                                                                                    \n"     
   
    "     uniform highp float  shininess;                                                                                                   \n"    
    "     uniform highp float  ambient;                                                                                                     \n" 
    //--------------------------------------------                                                                      
    "     varying highp  vec4  lightPosition_PASS;                                                                                          \n" 
    "     varying highp  vec2  varTexcoord;                                                                                                 \n" 
    //--------------------------------------------                                                                       
    "             highp  vec4  tempColor;                                                                                                   \n" 
    "             highp  vec4  specular;                                                                                                    \n"     
    //-------------------------------------------- 
                                                                
    //=======================================================================================================================                      
   
   "void main()                                                                                                                             \n" 
    "{                                                                                                                                      \n" 
                 //---------------------------------------------------------------------------------------------------------------------
    "            highp float comp = (shadowTexcoord.z / shadowTexcoord.w) - 8.4e-005;                                                       \n" 
    "            highp float depth_PowerVR = texture2DProj(ShadowTexture, shadowTexcoord).r;                                                \n" 
    "            highp float shadowVal = comp <= depth_PowerVR ? 1.0 : 0.4;                                                                 \n" 
                 //---------------------------------------------------------------------------------------------------------------------
    "            NormalTex       =  texture2D(NormalMap,  varTexcoord.xy).xyz;                                                              \n" 
    "            NormalTex       =  normalize((NormalTex  - 0.5));                                                                          \n" 
    "            NdotL1          =  max(dot(NormalTex, lightPosition_PASS.xyz), 0.0);                                                                 \n"   
    "            //----------------------------------------------------------------------------                                             \n"        

    "            //----------------------------------------------------------------------------                                             \n" 
    "            tempColor       =  texture2D(Texture1, varTexcoord.xy);                                                                    \n" 
    "	         specular        =  vec4(1.0, 1.0, 1.0, 1.0) * max(pow(NdotL1,  35.0), 0.0) * tempColor;                                   \n" 
    "            gl_FragColor    =  tempColor  * NdotL1 * NdotL1 + specular;                                      \n" 
    "}\n";

    
      //--------------------------------------------------------------------------------------------------                    

        hardShinyBumpPlastic_SHADER_VERTEX = glCreateShader( GL_VERTEX_SHADER);                                                          
        glShaderSource( hardShinyBumpPlastic_SHADER_VERTEX, 1, &vertexSource_hardShinyBumpPlastic, NULL );                                        
        glCompileShader( hardShinyBumpPlastic_SHADER_VERTEX);                                              //glShaderBinary                              
        //----------------------------------------------------                                                                  
        hardShinyBumpPlastic_SHADER_FRAGMENT = glCreateShader( GL_FRAGMENT_SHADER);                                                      
        glShaderSource( hardShinyBumpPlastic_SHADER_FRAGMENT, 1, &fragmentSource_hardShinyBumpPlastic, NULL );                                    
        glCompileShader(hardShinyBumpPlastic_SHADER_FRAGMENT);                                              //glShaderBinary                                                                             
        //--------------------------------------------------------------------------------------------------                    
        glAttachShader( hardShinyBumpPlastic_SHADER, hardShinyBumpPlastic_SHADER_VERTEX );                                                        
        glAttachShader( hardShinyBumpPlastic_SHADER, hardShinyBumpPlastic_SHADER_FRAGMENT );                                                      
        //--------------------------------------------------------------------------------------------------                    
        glBindAttribLocation(hardShinyBumpPlastic_SHADER,   0, "position");                                                              
        glBindAttribLocation(hardShinyBumpPlastic_SHADER,   1, "normal");                                                            
        glBindAttribLocation(hardShinyBumpPlastic_SHADER,   2, "textureCoords");                                                             
        //--------------------------------------------------------------------------------------------------                    
        glDeleteShader( hardShinyBumpPlastic_SHADER_VERTEX);                                                                             
        glDeleteShader( hardShinyBumpPlastic_SHADER_FRAGMENT);                                                                           
        glLinkProgram(hardShinyBumpPlastic_SHADER);                                                                                      
        //--------------------------------------------------------------------------------------------------                    
        UNIFORM_MODELVIEW_hardShinyBumpPlastic               = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "mvMatrix");                  
        UNIFORM_MODELVIEWPROJ_hardShinyBumpPlastic           = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "mvpMatrix");  
        //-------------------------------      
        UNIFORM_viewMatrix_hardShinyBumpPlastic              = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "viewMatrix");              
        //-------------------------------
        UNIFORM_SHADOW_PROJ_hardShinyBumpPlastic             = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "projectionShadow");                                                  
        UNIFORM_modelViewShadow_hardShinyBumpPlastic         = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "modelViewShadow");            
        //-------------------------------      
        UNIFORM_LIGHT_MATRIX_hardShinyBumpPlastic            = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "LightMatrix");                
        UNIFORM_TEXTURE_MATRIX_hardShinyBumpPlastic          = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "TextureMatrix");         
        //-----------------------------                                                                                         
        UNIFORM_LIGHT_POSITION_01_hardShinyBumpPlastic       = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "light_POSITION_01");          
        //----------------------------- 
        UNIFORM_shininess_hardShinyBumpPlastic               = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "shininess");  
        UNIFORM_ambient_hardShinyBumpPlastic                 = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "ambient");  
        //-----------------------------     
        UNIFORM_ShadowTexture_hardShinyBumpPlastic           = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "ShadowTexture");           
        UNIFORM_TEXTURE_DOT3_hardShinyBumpPlastic            = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "NormalMap");                  
        UNIFORM_TEXTURE_hardShinyBumpPlastic                 = glGetUniformLocation(hardShinyBumpPlastic_SHADER, "Texture1");  
