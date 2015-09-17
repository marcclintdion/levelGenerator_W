glUseProgram(rubber_SHADER);      
//================================================================================== 
 

   MultiplyMatrix(mvpMatrix, projection, modelView);                                                                                                                         
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(lightMatrix);                                                                                                                                                
    InvertMatrix(lightMatrix, modelView);                                                                                                                                     
    //---------------------------------------------------------------------------------------------------------------------------------------------------|__LIGHT             
    LoadIdentity(textureMatrix);
    //Translate(textureMatrix, shadowsPositionOffset[0], shadowsPositionOffset[1], shadowsPositionOffset[2]);
    //Scale(textureMatrix, scaleShadows, scaleShadows, scaleShadows);   
    //======================================================================================================                                                                  
    glVertexAttribPointer(0,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(0));                                                                                                  
    glEnableVertexAttribArray(0);	                                                                                                                                          
    glVertexAttribPointer(1,   3, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(12));                                                                                                 
    glEnableVertexAttribArray(1);  
    glVertexAttribPointer(2,   2, GL_FLOAT, GL_FALSE, 32, BUFFER_OFFSET(24));                                                                                                 
    glEnableVertexAttribArray(2);     
    //======================================================================================================                
    glUniformMatrix4fv(UNIFORM_MODELVIEWPROJ_rubber,   1,0,  mvpMatrix); 
    glUniformMatrix4fv(UNIFORM_MODELVIEW_rubber,       1,0,  modelView);                                                                                                          
    //---------------     
    glUniformMatrix4fv(UNIFORM_viewMatrix_rubber,      1,0,  viewMatrix);     
    //---------------  
    glUniformMatrix4fv(UNIFORM_SHADOW_PROJ_rubber,     1,0,  ProjectionShadow);   
    glUniformMatrix4fv(UNIFORM_modelViewShadow_rubber, 1,0,  modelViewShadow);     
    //----------------     
    glUniformMatrix4fv(UNIFORM_LIGHT_MATRIX_rubber,    1,0,  lightMatrix);
    glUniformMatrix4fv(UNIFORM_textureMatrix_rubber,   1,0,  textureMatrix);  
    //---------------------------------------------------------------------------------
  
    glUniform4f(UNIFORM_LIGHT_POSITION_01_rubber, rubber_LIGHT_POSITION_01[0], 
                                                  rubber_LIGHT_POSITION_01[1], 
                                                  rubber_LIGHT_POSITION_01[2], 
                                                  rubber_LIGHT_POSITION_01[3]);      
    //---------------------------------------------------------------------------------     
    glUniform1f(UNIFORM_SHININESS_rubber, rubber_SHININESS);  
    //---------------------------------------------------------------------------------       
    
    
    glUniform1i (UNIFORM_TEXTURE_DOT3_rubber, 1);                                                                                                                             
    glUniform1i (UNIFORM_TEXTURE_rubber, 0 );                                                                                                                                 
    //======================================================================================================                                                                  
