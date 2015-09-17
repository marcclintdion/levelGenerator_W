glUseProgram(shallowRound_SHADER);       
    //-------------------------------------------------------------------------------------------
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //-------------------------------------------------------------------------------------------
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //-------------------------------------------------------------------------------------------          
    LoadIdentity(textureMatrix);
    //===========================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);  
    glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));                                                                                                 
    glEnableVertexAttribArray(2);     
    glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));                                                                                                 
    glEnableVertexAttribArray(3);                                                                                                                                                
    //===========================================================================================               
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_shallowRound,     1,0,  mvpMatrix); 
    glUniformMatrix4fv(UNIFORM_MODELVIEW_shallowRound,         1,0,  modelView);     
    //---------------     
    glUniformMatrix4fv(UNIFORM_viewMatrix_shallowRound,        1,0,  viewMatrix);     
    //---------------  
    glUniformMatrix4fv(UNIFORM_SHADOW_PROJ_shallowRound,       1,0,  ProjectionShadow);   
    glUniformMatrix4fv(UNIFORM_modelViewShadow_shallowRound,   1,0,  modelViewShadow);     
    //----------------                                                                                                         
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_shallowRound,      1,0,  lightMatrix);
    glUniformMatrix4fv(UNIFORM_textureMatrix_shallowRound,     1,0,  textureMatrix);  
    //---------------------------------------------------------------------------------
    glUniform4f(UNIFORM_offset_shallowRound,                        offsetFinalShadow[0], 
                                                                 offsetFinalShadow[1], 
                                                                 offsetFinalShadow[2], 
                                                                 offsetFinalShadow[3]);      
    //---------------------------------------------------------------------------------    
    glUniform4f(UNIFORM_LIGHT_POSITION_01_shallowRound, shallowRound_LIGHT_POSITION_01[0], 
                                                     shallowRound_LIGHT_POSITION_01[1], 
                                                     shallowRound_LIGHT_POSITION_01[2], 
                                                     shallowRound_LIGHT_POSITION_01[3]);        
    //---------------------------------------------------------------------------------     
    glUniform1f(UNIFORM_SHININESS_shallowRound, shallowRound_SHININESS);  
    //---------------------------------------------------------------------------------    
    glUniform1f(UNIFORM_CONSTANT_ATTENUATION_shallowRound,  steepPointy_constantAttenuation);     
    glUniform1f(UNIFORM_LINEAR_ATTENUATION_shallowRound,    steepPointy_linearAttenuation); 
    glUniform1f(UNIFORM_QUADRATIC_ATTENUATION_shallowRound, steepPointy_quadraticAttenuation);    
    //---------------------------------------------------------------------------------    
    glUniform1i (UNIFORM_TEXTURE_LightMap_shallowRound, 4);     
    glUniform1i (UNIFORM_TEXTURE_SHADOW_shallowRound, 3);      
    glUniform1i (UNIFORM_TEXTURE_HEIGHT_shallowRound, 2);     
    glUniform1i (UNIFORM_TEXTURE_DOT3_shallowRound, 1);                                                                                                                             
    glUniform1i (UNIFORM_TEXTURE_shallowRound, 0 );         
    
//---------------------------------------------------------------
glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);                                                                                                                          
//---     
