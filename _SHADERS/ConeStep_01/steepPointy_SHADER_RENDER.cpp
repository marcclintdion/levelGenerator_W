glUseProgram(steepPointy_SHADER);   
    
    MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //------------------------------------------------------------------------------------------------------            
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //------------------------------------------------------------------------------------------------------     
    LoadIdentity(textureMatrix);
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);  
    glVertexAttribPointer(2,   3, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(24));                                                                                                 
    glEnableVertexAttribArray(2);     
    glVertexAttribPointer(3,   2, GL_FLOAT, GL_FALSE, 44, BUFFER_OFFSET(36));                                                                                                 
    glEnableVertexAttribArray(3);                                                                                                                                                
    //======================================================================================================                
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_steepPointy,   1,0,  mvpMatrix); 
    glUniformMatrix4fv(UNIFORM_MODELVIEW_steepPointy,       1,0,  modelView);                                                                                                          
    //---------------     
    glUniformMatrix4fv(UNIFORM_viewMatrix_steepPointy,      1,0,  viewMatrix);     
    //---------------     
    glUniformMatrix4fv(UNIFORM_SHADOW_PROJ_steepPointy,     1,0,  ProjectionShadow);
    glUniformMatrix4fv(UNIFORM_modelViewShadow_steepPointy, 1,0,  modelViewShadow);    
    //--------------- 
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_steepPointy,    1,0,  lightMatrix);  
    glUniformMatrix4fv(UNIFORM_textureMatrix_steepPointy,   1,0,  textureMatrix);      
    glUniformMatrix4fv(UNIFORM_INVERSEMATRIX_steepPointy,   1,0,  modelView);                                                                                                           
    //---------------------------------------------------------------------------------
    glUniform4f(UNIFORM_offset_steepPointy,                      offsetFinalShadow[0], 
                                                                 offsetFinalShadow[1], 
                                                                 offsetFinalShadow[2], 
                                                                 offsetFinalShadow[3]);      
    //---------------------------------------------------------------------------------    
    glUniform4f(UNIFORM_LIGHT_POSITION_01_steepPointy, steepPointy_LIGHT_POSITION_01[0], 
                                                       steepPointy_LIGHT_POSITION_01[1], 
                                                       steepPointy_LIGHT_POSITION_01[2], 
                                                       steepPointy_LIGHT_POSITION_01[3]);        
    //---------------------------------------------------------------------------------    
    glUniform1f(UNIFORM_CONSTANT_ATTENUATION_steepPointy,  steepPointy_constantAttenuation);    
    glUniform1f(UNIFORM_LINEAR_ATTENUATION_steepPointy,    steepPointy_linearAttenuation);     
    glUniform1f(UNIFORM_QUADRATIC_ATTENUATION_steepPointy, steepPointy_quadraticAttenuation);    
    //---------------------------------------------------------------------------------     
    glUniform1f(UNIFORM_SHININESS_steepPointy, steepPointy_SHININESS);     
    //---------------------------------------------------------------------------------    
    glUniform1i (UNIFORM_TEXTURE_SHADOW_steepPointy, 3);      
    glUniform1i (UNIFORM_TEXTURE_HEIGHT_steepPointy, 2);     
    glUniform1i (UNIFORM_TEXTURE_DOT3_steepPointy,   1);                                                                                                                             
    glUniform1i (UNIFORM_TEXTURE_steepPointy,        0);    

//---------------------------------------------------------

glActiveTexture ( GL_TEXTURE3 );                                                                                                                                          
glBindTexture(GL_TEXTURE_2D, m_uiShadowMapTexture);                                                                                                                          
//---     
